#ifndef CONDITION_WAITER_HXX
#define CONDITION_WAITER_HXX

#include "condition_waiter.hpp"
#include "mutex.hpp"

namespace advcpp {

template <class BoolFunctor>
ConditionWaiter::ConditionWaiter(experis::ConditionVariable& a_cv, experis::Mutex& m_lockedMutex, BoolFunctor a_condition)
{
    while(a_condition()){
        a_cv.WaitToBeNotified(m_lockedMutex);
    }
}

} //advcpp


#endif //CONDITION_WAITER_HXX