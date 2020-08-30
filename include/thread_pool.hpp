#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <vector>
#include "i_mt_priority_queue.hpp"
#include "sharedptr.hpp"
#include "common.hpp"
#include "thread.hpp"
#include "thread_group.hpp"
#include "mutex.hpp"
#include "semaphore.hpp"
#include "condition_variable.hpp"

namespace advcpp {

class ThreadPool : private UnCopyable {
public:
    typedef Runnable Task;
    typedef SharedPtr<Task> TaskPtr;
    typedef experis::IMTQueue<TaskPtr> TaskContainer;
    typedef SharedPtr<TaskContainer> TaskContainerPtr;

public:
    explicit ThreadPool(size_t a_numOfThreads, size_t a_poolSize);
    ~ThreadPool();

    void Submit(TaskPtr a_task);
    //bool TrySubmit(Command);
    void ShutdownNow(std::vector<TaskPtr> &a_pending);   
    size_t GraceFullShutdown(size_t a_timeOut_ms = 0);
    size_t PendingTasks() const;
    void Add(size_t a_threads);
    void Remove(size_t a_threads);

private:
    void executeRoutine();
    void pushEmptyTasks();
    void executeTasksWithTimeOut(size_t a_timeOut_ms);

private:
    class Executer;
    class DoNothing;
    enum PoolStatus {
        STATUS_WORK,
        STATUS_STOP,
        STATUS_REMOVE,
        STATUS_STOP_IN_PROGRESS,
        STATUS_STOP_IN_PROGRESS_TIMEOUT
    };

private:
    TaskContainerPtr m_tasks;
    AtomicValue<PoolStatus> m_status;
    ThreadGroup m_threads;
    AtomicValue<pthread_t> m_threadIdToJoin;
    experis::Semaphore m_postThreadIdWaitingRoom;
    experis::Semaphore m_pullThreadIdWaitingRoom;
    AtomicValue<size_t> m_numOfTasks;
    experis::Mutex m_addRemoveLock;
};    

} //advcpp

#endif //THREAD_POOL_HPP
