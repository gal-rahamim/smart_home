#ifndef CONDITION_VARIABLE_HPP
#define CONDITION_VARIABLE_HPP

#include <pthread.h>

namespace experis {

class Mutex;

class ConditionVariable {
public:
    ConditionVariable();
    ~ConditionVariable();

    void NotifyAll();
    void NotifyOne();
    void WaitToBeNotified(Mutex &_lockedMutex);
private:
    ConditionVariable(const ConditionVariable&);
    ConditionVariable& operator=(const ConditionVariable&);

private:
    pthread_cond_t m_cond;
};

}//experis

#endif //CONDITION_VARIABLE_HPP
