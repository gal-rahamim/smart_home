#ifndef MT_CYCLIC_BUFFER_CV_HPP
#define MT_CYCLIC_BUFFER_CV_HPP

#include "i_mt_priority_queue.hpp"
#include "condition_variable.hpp"
#include "mutex.hpp"

namespace experis {

template <class T>
class MTCyclicBufferCV : public IMTQueue<T> {
public:
    MTCyclicBufferCV(size_t _size);
    ~MTCyclicBufferCV();

    virtual void Enqueue(const T& _val);
    virtual void Dequeue(T& _res);
    virtual size_t Size() const;

private:
    MTCyclicBufferCV(const MTCyclicBufferCV&);
    MTCyclicBufferCV& operator=(const MTCyclicBufferCV&);

    T* m_buffer;
    ConditionVariable m_enqWaiting;
    ConditionVariable m_deqWaiting;
    Mutex m_bufferLock;
    size_t m_size;
    size_t m_front;
    size_t m_back;
    size_t m_freeSpace;
};

} //experis

#include "inl/mt_cyclic_buffer_cv_inl.hxx"

#endif //MT_CYCLIC_BUFFER_CV_HPP
