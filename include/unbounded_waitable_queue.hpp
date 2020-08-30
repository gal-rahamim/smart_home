#ifndef UNBOUNDED_WAITABLE_QUEUE_HPP
#define UNBOUNDED_WAITABLE_QUEUE_HPP

#include <queue>
#include "condition_variable.hpp"
#include "mutex.hpp"
#include "common.hpp"
#include "atomic_value.hpp"

namespace advcpp {

template <class T>
class UnboundedWaitableQueue : private UnCopyable {
public:
    UnboundedWaitableQueue();

    void Enqueue(const T& a_object);
    void Dequeue(T& a_res);
    size_t Size() const;
    bool Empty() const;
    void SafeShutdown();
    void WaitForQueueToEmpty();

private:
    std::queue<T> m_queue;
    mutable experis::Mutex m_lock;
    experis::ConditionVariable m_dequeueWaiting;
    experis::ConditionVariable m_emptyWaiting;
    AtomicValue<size_t> m_emptyWaitFlag;
    AtomicValue<size_t> m_threadsWaiting;
    AtomicValue<size_t> m_flag;
};

} //advcpp

#include "inl/unbounded_waitable_queue.hxx"

#endif //UNBOUNDED_WAITABLE_QUEUE_HPP