#ifndef UNBOUNDED_WAITABLE_QUEUE_HXX
#define UNBOUNDED_WAITABLE_QUEUE_HXX

#include <unistd.h>
#include "unbounded_waitable_queue.hpp"
#include "locker.hpp"
#include "condition_waiter.hpp"
// #include "incrementor.hpp"

namespace advcpp {

template <class T>
UnboundedWaitableQueue<T>::UnboundedWaitableQueue()
: m_queue()
, m_lock()
, m_dequeueWaiting()
, m_emptyWaiting()
, m_emptyWaitFlag()
, m_threadsWaiting()
, m_flag()
{
}

template <class T>
void UnboundedWaitableQueue<T>::SafeShutdown() 
{
    if(m_threadsWaiting.Value() > 0) {
        ++m_flag;
        Locker guard(m_lock); 
        m_dequeueWaiting.NotifyAll();
    }
    usleep(20);
}

template <class T>
struct EmptyQueueCond {
    EmptyQueueCond(const std::queue<T>& a_q)
    : m_q(a_q)
    {}
    bool operator()() const {
        return (m_q.size() > 0) ;
    }
    const std::queue<T>& m_q;
};

template <class T>
void UnboundedWaitableQueue<T>::WaitForQueueToEmpty()
{
    ++m_emptyWaitFlag;
    Locker guard(m_lock);
    {
        ConditionWaiter waiter(m_emptyWaiting, m_lock, EmptyQueueCond<T>(m_queue));
    }
} 

template <class T>
void UnboundedWaitableQueue<T>::Enqueue(const T& a_object)
{
    Locker guard(m_lock);
    m_queue.push(a_object);
    if(m_threadsWaiting.Value() > 0) {
        m_dequeueWaiting.NotifyOne();
    }
}

template <class T>
struct SizeEqualZeroCond {
    SizeEqualZeroCond(const std::queue<T>& a_q, AtomicValue<size_t>& a_flag)
    : m_q(a_q)
    , m_f(a_flag)
    {}
    bool operator()() const {
        return (m_q.size() == 0 && m_f.Value() == 0) ;
    }
    const std::queue<T>& m_q;
    AtomicValue<size_t>& m_f;
};

struct Incrementor {
    Incrementor(AtomicValue<size_t>& a_toInc) 
    : m_toInc(a_toInc)
    {
        ++m_toInc;
    }
    ~Incrementor() {
        --m_toInc;
    }
    AtomicValue<size_t>& m_toInc;
};

template <class T>
void UnboundedWaitableQueue<T>::Dequeue(T& a_res)
{
    Locker guard(m_lock);
    {
        Incrementor inc(m_threadsWaiting);
        ConditionWaiter waiter(m_dequeueWaiting, m_lock, SizeEqualZeroCond<T>(m_queue, m_flag));
        if(m_flag.Value() == 1) {
            return;
        }
    }
    a_res = m_queue.front();
    m_queue.pop();
    if(m_emptyWaitFlag.Value() == 1) {
        m_emptyWaiting.NotifyOne();
    }
}

template <class T>
size_t UnboundedWaitableQueue<T>::Size() const
{
    Locker guard(m_lock);
    return m_queue.size();
}

template <class T>
bool UnboundedWaitableQueue<T>::Empty() const
{
    return (0 == Size());
}

} //advcpp

#endif //UNBOUNDED_WAITABLE_QUEUE_HXX