#include <assert.h>
#include <errno.h>
#include "mutex.hpp"
#include "condition_variable.hpp"
#include "mutex_exceptions.hpp"

namespace experis {

ConditionVariable::ConditionVariable()
{
    int result = pthread_cond_init(&m_cond, 0);
    if(0 != result) {
        assert(result != EBUSY);
        assert(result != EINVAL);
        assert(result != EAGAIN);
        assert(result != ENOMEM);
    }
}
ConditionVariable::~ConditionVariable() 
{
    int result = pthread_cond_destroy(&m_cond);
    if(0 != result) {
        assert(result != EBUSY);
        assert(result != EINVAL);
    }
}

void ConditionVariable::WaitToBeNotified(Mutex &_lockedMutex) 
{
    int result = pthread_cond_wait(&m_cond, _lockedMutex.getCMutex());
    if(-1 == result) {
        assert(!"wait error");
    }
}

void ConditionVariable::NotifyOne() 
{
    int result  = pthread_cond_signal(&m_cond);
    if(-1 == result) {
        assert(!"signal error");
    }
}

void ConditionVariable::NotifyAll() 
{
    int result  = pthread_cond_broadcast(&m_cond);
    if(-1 == result) {
        assert(!"broadcast error");
    }
}

} //experis
