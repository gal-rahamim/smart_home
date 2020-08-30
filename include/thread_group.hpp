#ifndef THREAD_GROUP_HPP
#define THREAD_GROUP_HPP

#include <vector>
#include "sharedptr.hpp"
#include "thread.hpp"
#include "mutex.hpp"

namespace advcpp {

class ThreadGroup {
public:
    typedef Runnable Task;
    typedef std::tr1::shared_ptr<Task> TaskPtr;

public:
    ThreadGroup(size_t a_numOfThreads, TaskPtr a_task_ptr);
    ~ThreadGroup();

    void Add(size_t a_numOfThreads, TaskPtr a_task_ptr);
    void Remove(size_t a_numOfThreads);
    size_t Size() const;
    void Cancel();
    void Join();
    void JoinById(pthread_t a_trd);

private:
    typedef SharedPtr<experis::Thread> ThreadPtr;
    typedef std::vector<ThreadPtr> ThreadContainer;

private:
    ThreadContainer m_threads;
    experis::Mutex m_lock;
    AtomicValue<size_t> m_numOfThreads;

};

} //advcpp

#endif //THREAD_GROUP_HPP