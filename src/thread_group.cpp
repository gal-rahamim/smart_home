#include "thread_group.hpp"

namespace advcpp {

ThreadGroup::ThreadGroup(size_t a_numOfThreads, TaskPtr a_task_ptr)
: m_threads()
, m_lock()
, m_numOfThreads()
{
    Add(a_numOfThreads, a_task_ptr);
}    

ThreadGroup::~ThreadGroup()
{
    Join();
}

void ThreadGroup::Add(size_t a_numOfThreads, TaskPtr a_task_ptr)
{
    m_lock.Lock();
    for(size_t i = 0 ; i < a_numOfThreads ; ++i) {
        m_threads.push_back(ThreadPtr(new experis::Thread(a_task_ptr)));
        ++m_numOfThreads;
    }
    m_lock.UnLock();
}

void ThreadGroup::Remove(size_t a_numOfThreads)
{
    m_lock.Lock();
    for(size_t i = 0 ; i < a_numOfThreads ; ++i) {
        m_threads.pop_back();
        --m_numOfThreads;
    }    
    m_lock.UnLock();
}

size_t ThreadGroup::Size() const
{
    return m_numOfThreads.Value();
}

void ThreadGroup::Cancel()
{
    m_lock.Lock();
    for(size_t i = m_threads.size() - 1 ; i >= 0 && m_threads.size() > 0 ; --i) {
        m_threads[i]->Cancel();
        m_threads[i]->Join();
        m_threads.pop_back();
        --m_numOfThreads;
    }        
    m_lock.UnLock();
}

void ThreadGroup::Join()
{
    m_lock.Lock();
    for(size_t i = m_threads.size() - 1 ; i >= 0 && m_threads.size() > 0 ; --i) {
        m_threads[i]->Join();
        m_threads.pop_back();
        --m_numOfThreads;
    }        
    m_lock.UnLock();
}

void ThreadGroup::JoinById(pthread_t a_trd)
{
    m_lock.Lock();
    for(ThreadContainer::iterator iter = m_threads.begin() ; iter != m_threads.end() ; ++iter) {
        if(**iter == a_trd) {
            (*iter)->Join();
            m_threads.erase(iter);
            --m_numOfThreads;
            break;
        }
    }        
    m_lock.UnLock();
}

} //advcpp