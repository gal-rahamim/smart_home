#ifndef CONDITION_WAITER_HPP
#define CONDITION_WAITER_HPP

#include "condition_variable.hpp"

namespace advcpp {
    
class ConditionWaiter {    
public:
    template <class BoolFunctor>
    ConditionWaiter(experis::ConditionVariable& a_cv, experis::Mutex& m_lockedMutex, BoolFunctor a_condition);
};

} //advcpp

#include "inl/condition_waiter.hxx"

#endif //CONDITION_WAITER_HPP