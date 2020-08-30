#ifndef ATOMIC_BOOL_HXX
#define ATOMIC_BOOL_HXX

#include "atomic_bool.hpp"

namespace advcpp {

AtomicBool::AtomicBool(int a_init)
: m_value(a_init)
{
}

inline bool AtomicBool::Value() const
{
    return __sync_add_and_fetch(&m_value, 0);

}
inline bool AtomicBool::Flip()
{
    return __sync_xor_and_fetch(&m_value, 1);
}


} //advcpp


#endif //ATOMIC_BOOL_HXX