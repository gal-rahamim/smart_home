#ifndef ATOMIC_BOOL_HPP
#define ATOMIC_BOOL_HPP

namespace advcpp {

class AtomicBool : private UnCopyable {
public:
    explicit AtomicBool(int a_init = false);

    bool Value() const;
    bool Flip();

private:
    mutable int m_value;
};

} //advcpp

#include "inl/atomic_bool.hxx"


#endif //ATOMIC_BOOL_HPP