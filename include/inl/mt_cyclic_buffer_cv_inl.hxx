#ifndef MT_CYCLIC_BUFFER_CV_INL_HPP
#define MT_CYCLIC_BUFFER_CV_INL_HPP

#include <assert.h>
#include "mt_cyclic_buffer_cv.hpp"
#include "mutex_exceptions.hpp"

namespace experis {

template<class T>
MTCyclicBufferCV<T>::MTCyclicBufferCV(size_t _size)
: m_buffer(new T[_size])
, m_enqWaiting()
, m_deqWaiting()
, m_bufferLock()
, m_size(_size)
, m_front(0)
, m_back(0)
, m_freeSpace(_size) {
}

template<class T>
MTCyclicBufferCV<T>::~MTCyclicBufferCV() {
    delete[] m_buffer;
}

template<class T>
void MTCyclicBufferCV<T>::Enqueue(const T& _val) {
    try {
        m_bufferLock.Lock();
    }
    catch(const std::exception &_ex) {
        assert(!_ex.what());
    }
    while(!(m_freeSpace > 0)) {
        m_enqWaiting.WaitToBeNotified(m_bufferLock);
    }
    try{
        m_buffer[m_back] = _val;
        ++m_back;
        m_back %= m_size;
        --m_freeSpace;
    }
    catch(...) {
        try {
            m_bufferLock.UnLock();
        }
        catch(const std::exception &_ex) {
            assert(!_ex.what());
        }
        throw;
    }
    try {
        m_bufferLock.UnLock();
    }
    catch(const std::exception &_ex) {
        assert(!_ex.what());
    }
    m_deqWaiting.NotifyOne();
}

template<class T>
void MTCyclicBufferCV<T>::Dequeue(T& _res) {
    try {
        m_bufferLock.Lock();
    }
    catch(const std::exception &_ex) {
        assert(!_ex.what());
    }
    while(!(m_freeSpace < m_size)) {
        m_deqWaiting.WaitToBeNotified(m_bufferLock);
    }
    try {
        _res = m_buffer[m_front];
        ++m_front;
        m_front %= m_size;
        ++m_freeSpace;
    }
    catch(...) {
        try {
            m_bufferLock.UnLock();
        }
        catch(const std::exception &_ex) {
            assert(!_ex.what());
        }
        throw;
    }
    try {
        m_bufferLock.UnLock();
    }
    catch(const std::exception &_ex) {
        assert(!_ex.what());
    }
    m_enqWaiting.NotifyOne();
}

template<class T>
size_t MTCyclicBufferCV<T>::Size() const
{
    try {
        m_bufferLock.Lock();
    }
    catch(const std::exception &_ex) {
        assert(!_ex.what());
    }
    size_t ret = m_size - m_freeSpace;
    try {
    m_bufferLock.UnLock();
    }
    catch(const std::exception &_ex) {
        assert(!_ex.what());
    }
    return ret;
}
} //experis
#endif //MT_CYCLIC_BUFFER_CV_INL_HPP
