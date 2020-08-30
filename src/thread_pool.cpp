#include <iostream>
#include <unistd.h>
#include <cxxabi.h>
#include <climits>
#include "thread_pool.hpp"
#include "mt_cyclic_buffer_cv.hpp"

namespace advcpp {

class ThreadPool::Executer : public Runnable {
public:
    Executer(ThreadPool& a_pool);
    virtual void Run();
private:
    ThreadPool& m_pool;
};

class ThreadPool::DoNothing : public Runnable {
public:
    virtual void Run();
}; 

ThreadPool::ThreadPool(size_t a_numOfThreads, size_t a_poolSize)
: m_tasks(TaskContainerPtr(new experis::MTCyclicBufferCV<TaskPtr>(a_poolSize)))
, m_status(STATUS_WORK)
, m_threads(a_numOfThreads, std::tr1::shared_ptr<Runnable>(new Executer(*this)))
, m_threadIdToJoin()
, m_postThreadIdWaitingRoom(1)
, m_pullThreadIdWaitingRoom(0)
, m_numOfTasks()
, m_addRemoveLock()
{
    // if(0 != a_poolSize) {
    //     m_tasks = TaskContainerPtr(new experis::MTCyclicBufferCV<TaskPtr>(a_poolSize));
    // }
    // else {
    //     //TODO phase2
    // }
}

ThreadPool::~ThreadPool()
{
    GraceFullShutdown();
}

void ThreadPool::Submit(TaskPtr a_task)
{
    if(STATUS_WORK == m_status.Value()) {
        ++m_numOfTasks;
        m_tasks->Enqueue(a_task);
    }
    else {
        throw std::runtime_error("Can't submit - ThreadPool is closed");
    }
}

size_t ThreadPool::PendingTasks() const
{
    return m_numOfTasks.Value();
}

void ThreadPool::ShutdownNow(std::vector<TaskPtr> &a_pending)
{
    m_status = STATUS_STOP;
    m_threads.Cancel();
    for(size_t i = 0 ; i < m_tasks->Size() ; ++i) {
        TaskPtr pt;
        m_tasks->Dequeue(pt);
        a_pending.push_back(pt);
    }
}

void ThreadPool::pushEmptyTasks() 
{
    size_t emptyTasksToEnqueue =  m_numOfTasks.Value() > m_threads.Size() ? 0 : m_threads.Size() - m_numOfTasks.Value();
    TaskPtr dn(new ThreadPool::DoNothing);
    for(size_t i = 0 ; i < emptyTasksToEnqueue ; ++i) {
        ++m_numOfTasks;
        m_tasks->Enqueue(dn);
    }
}

static double calcTimeInMs(const struct timespec& a_start)
{
    struct timespec finish;
    clock_gettime(CLOCK_MONOTONIC, &finish);
    double elapsed = (finish.tv_sec - a_start.tv_sec);
    elapsed += (finish.tv_nsec - a_start.tv_nsec) / 1000000000.0;
    return elapsed*1000;
}

void ThreadPool::executeTasksWithTimeOut(size_t a_timeOut_ms)
{
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    pushEmptyTasks();
    while(calcTimeInMs(start) < a_timeOut_ms && m_threads.Size() > 0) {
        m_pullThreadIdWaitingRoom.Wait();
        m_threads.JoinById(m_threadIdToJoin.Value());
        m_postThreadIdWaitingRoom.Post();
    }
} 

size_t ThreadPool::GraceFullShutdown(size_t a_timeOut_ms)
{
    if(m_status.Value() != STATUS_WORK && m_status.Value() != STATUS_STOP) {
        throw std::runtime_error("stop is allready in progress");
    }
    if(0 == a_timeOut_ms) {
        m_status = STATUS_STOP_IN_PROGRESS;
        pushEmptyTasks();
        m_threads.Join();
    }
    else {
        m_status = STATUS_STOP_IN_PROGRESS_TIMEOUT;
        executeTasksWithTimeOut(a_timeOut_ms);
    }
    m_status = STATUS_STOP;
    return m_numOfTasks.Value();
}

void ThreadPool::Add(size_t a_threads)
{
    if(m_status.Value() != STATUS_WORK) {
        throw std::runtime_error("Can't add - ThreadPool is closed");
    }
    m_addRemoveLock.Lock();
    std::tr1::shared_ptr<Runnable> runP(new Executer(*this));
    m_threads.Add(a_threads, runP);
    m_addRemoveLock.UnLock();
}

void ThreadPool::Remove(size_t a_threads)
{
    if(m_status.Value() != STATUS_WORK) {
        throw std::runtime_error("Can't remove - ThreadPool is closed");
    }
    m_addRemoveLock.Lock();
    m_status = STATUS_REMOVE;
    assert(a_threads <= m_threads.Size());
    TaskPtr dn(new ThreadPool::DoNothing);
    size_t emptyTasksToEnqueue =  m_numOfTasks.Value() > a_threads ? 0 : a_threads - m_numOfTasks.Value();
    for(size_t i = 0 ; i < emptyTasksToEnqueue ; ++i) {
        ++m_numOfTasks;
        m_tasks->Enqueue(dn);
    }
    AtomicValue<size_t> removeCounter(a_threads);
    while(removeCounter.Value() > 0) {
        m_pullThreadIdWaitingRoom.Wait();
        m_threads.JoinById(m_threadIdToJoin.Value());
        --removeCounter;
        m_postThreadIdWaitingRoom.Post();
    }
    m_status = STATUS_WORK;
    m_addRemoveLock.UnLock();
}

void ThreadPool::executeRoutine()
{
    while(STATUS_WORK == m_status.Value()) {
        TaskPtr pt;
        m_tasks->Dequeue(pt);
        --m_numOfTasks;
        try {
            pt->Run();
        }
        catch(abi::__forced_unwind& x) {
            throw;
        }
        catch(std::exception& ex) {
            std::cerr << "Task throwed exception: " << ex.what() << std::endl;
        }
        catch(...) {
            std::cerr << "Don't throw these kind of exceptions!!" << std::endl;
            assert(0); 
        }
    }
    if(STATUS_REMOVE == m_status.Value() || STATUS_STOP_IN_PROGRESS_TIMEOUT == m_status.Value()) {
        m_postThreadIdWaitingRoom.Wait();
        m_threadIdToJoin = pthread_self();
        m_pullThreadIdWaitingRoom.Post();
    }
    if(STATUS_WORK == m_status.Value()) {
        m_pullThreadIdWaitingRoom.Wait();
        executeRoutine();
    }
}

ThreadPool::Executer::Executer(ThreadPool& a_pool)
: m_pool(a_pool)
{
}

void ThreadPool::Executer::Run()
{
    m_pool.executeRoutine();
}

void ThreadPool::DoNothing::Run()
{
}

} //advcpp
