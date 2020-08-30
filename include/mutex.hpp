#ifndef MUTEX_HPP
#define MUTEX_HPP

#include <pthread.h>
#include "condition_variable.hpp"

namespace experis {

class Mutex {
public:
    Mutex();
    ~Mutex();

    void Lock() const;
    void UnLock() const;
private:
    Mutex(const Mutex&); //no copy
    Mutex& operator=(const Mutex&); //no copy
    
    friend void ConditionVariable::WaitToBeNotified(Mutex&);
    pthread_mutex_t* getCMutex() const;

private:
    mutable pthread_mutex_t m_mutex;
};

inline pthread_mutex_t* Mutex::getCMutex() const
{
    return &m_mutex;
}

} //experis

#endif //MUTEX_HPP
