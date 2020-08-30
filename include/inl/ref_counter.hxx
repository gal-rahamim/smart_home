#ifndef REF_COUNTER_HXX
#define REF_COUNTER_HXX

#include "ref_counter.hpp"

namespace advcpp {

template <typename P, typename C> 
RefCounter<P, C>::RefCounter(P* a_ptr)
: m_ptr(a_ptr)
, m_counter(0)
{
    try {
        if(m_ptr) {
            m_counter = new AtomicValue<size_t>(1);
        }
    }
    catch(...) {
        delete m_ptr;
        throw;
    }
}

template <typename P, typename C> 
RefCounter<P, C>::~RefCounter()
{
    if(m_ptr && --*m_counter == 0) {
        delete m_ptr;
        delete m_counter;
    }   
}

template <typename P, typename C> 
RefCounter<P, C>::RefCounter(const RefCounter& a_other)
: m_ptr(a_other.m_ptr) 
, m_counter(a_other.m_counter)
{
    if(m_ptr) {
        ++*m_counter;
    }    
}

template <typename P, typename C> 
RefCounter<P, C>& RefCounter<P, C>::operator=(const RefCounter& a_other)
{
    if(this != &a_other) {
        Reset();
        m_ptr = a_other.m_ptr;
        m_counter = a_other.m_counter;
        if(m_ptr) {
            ++*m_counter;
        }
    }
    return *this;
}

template <typename P, typename C> 
template <typename D, typename E>
RefCounter<P, C>::RefCounter(RefCounter<D, E>& a_other)
: m_ptr(a_other.m_ptr) 
, m_counter(a_other.m_counter)
{
    if(m_ptr) {
        ++*m_counter;
    }    
}

template <typename P, typename C> 
template <typename D, typename E>
RefCounter<P, C>& RefCounter<P, C>::operator=(RefCounter<D, E>& a_other)
{
    Reset();
    m_ptr = a_other.m_ptr;
    m_counter = a_other.m_counter;
    if(m_ptr) {
        ++*m_counter;
    }
    return *this;
}

template <typename P, typename C> 
C RefCounter<P, C>::Usage() const
{
    if(m_ptr) {
        return m_counter->Value();
    }
    else {
        return 0;
    }
}

template <typename P, typename C> 
void RefCounter<P, C>::Reset()
{
    if(m_ptr) {
        --*m_counter;
    }
    m_ptr = 0;
    m_counter = 0;
}

} //advcpp

#endif //REF_COUNTER_HXX