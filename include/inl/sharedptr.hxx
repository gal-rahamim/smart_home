#include "sharedptr.hpp"

namespace advcpp {

template <typename T>
SharedPtr<T>::SharedPtr(T* a_ptr)
: m_ptr(a_ptr)
, m_refCount(a_ptr)
{
}

template <typename T>
template <typename D>
SharedPtr<T>::SharedPtr(SharedPtr<D>& a_other)
: m_ptr(a_other.m_ptr)
, m_refCount(a_other.m_refCount)
{
}

template <typename T>
template <typename D>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<D>& a_other)
{
    m_ptr = a_other.m_ptr;
    m_refCount = a_other.m_refCount;
    return *this;
}

template <typename T>
size_t SharedPtr<T>::Usage() const
{
    return m_refCount.Usage();
}

template <typename T>
inline const T& SharedPtr<T>::operator*() const
{
    return *m_ptr;
}

template <typename T>
inline T& SharedPtr<T>::operator*()
{
    return *m_ptr;
}

template <typename T>
inline const T* SharedPtr<T>::operator->() const
{
    return m_ptr;
}

template <typename T>
inline T* SharedPtr<T>::operator->()
{
    return m_ptr;
}

template <typename T>
inline T* SharedPtr<T>::operator&()
{
    return m_ptr;
}

template <typename T>
inline const T* SharedPtr<T>::operator&() const
{
    return m_ptr;
}

template <typename T, typename D>
bool operator==(const SharedPtr<T>& a_a, const SharedPtr<D>& a_b)
{
    return &a_a == &a_b;
}

template <typename T, typename D>
bool operator!=(const SharedPtr<T>& a_a, const SharedPtr<D>& a_b)
{
    return !(a_a == a_b);
}

template <typename T>
void SharedPtr<T>::Reset()
{
    m_refCount.Reset();
}

template <typename T>
void SharedPtr<T>::secret() const
{
    throw 1;
}

template <typename T>
inline SharedPtr<T>::operator PF() const
{
    return m_ptr ? &SharedPtr::secret : 0;
}


} //advcpp
