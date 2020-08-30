#ifndef ATOMIC_VALUE_HPP
#define ATOMIC_VALUE_HPP

#include "common.hpp"

namespace advcpp {

template <typename T>
class AtomicValue : private UnCopyable {
public:
    explicit AtomicValue(T a_init = T(0));
    AtomicValue& operator=(T a_val);

    T Value() const;
    T operator++();
    T operator--();

private:
    mutable T m_value;
};

} //advcpp

#include "inl/atomic_value.hxx"


#endif //ATOMIC_VALUE_HPP