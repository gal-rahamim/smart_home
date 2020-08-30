#ifndef ATOMIC_VALUE_HXX
#define ATOMIC_VALUE_HXX

namespace advcpp {

#include "atomic_value.hpp"

template <typename T>
AtomicValue<T>::AtomicValue(T a_init)
: m_value(a_init)
{
}

template <typename T>
AtomicValue<T>& AtomicValue<T>::operator=(T a_val)
{
    __sync_bool_compare_and_swap(&m_value, m_value, a_val);
    return *this;
} 

template <typename T>
T AtomicValue<T>::Value() const
{
    return __sync_add_and_fetch(&m_value, 0);
}

template <typename T>
T AtomicValue<T>::operator++()
{
    return __sync_add_and_fetch(&m_value, 1);
}

template <typename T>
T AtomicValue<T>::operator--()
{
    return __sync_sub_and_fetch(&m_value, 1);
}


} //advcpp

#endif //ATOMIC_VALUE_HXX
