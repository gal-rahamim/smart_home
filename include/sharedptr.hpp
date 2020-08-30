#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include <stddef.h>
#include "common.hpp"
#include "ref_counter.hpp"

namespace advcpp {

template <typename T>
class SharedPtr {
public:
    explicit SharedPtr(T* a_ptr = 0);

    template <typename D>
    SharedPtr(SharedPtr<D>& a_other);

    template <typename D>
    SharedPtr& operator=(SharedPtr<D>& a_other);

    typedef void (SharedPtr::*PF)() const;
    operator PF() const;
    const T& operator*() const;
    T& operator*();
    const T* operator->() const;
    T* operator->();
    T* operator&();
    const T* operator&() const;

    size_t Usage() const;
    void Reset();
private:
    void secret() const;
    template<typename D>
    friend class SharedPtr;
    
private:
    T* m_ptr;
    RefCounter<T, size_t> m_refCount;
};

template <typename T, typename D>
bool operator==(const SharedPtr<T>& a_a, const SharedPtr<D>& a_b);
template <typename T, typename D>
bool operator!=(const SharedPtr<T>& a_a, const SharedPtr<D>& a_b);

} //advcpp

#include "inl/sharedptr.hxx"

#endif //SHARED_PTR_HPP
