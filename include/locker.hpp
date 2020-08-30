#ifndef LOCKER_HPP
#define LOCKER_HPP

#include "common.hpp"
#include "mutex.hpp"

namespace advcpp {

class Locker :  private UnCopyable {
public:
    Locker(experis::Mutex& a_lock);
    ~Locker();

private:
    experis::Mutex& m_lock;
};

inline Locker::Locker(experis::Mutex& a_lock) 
: m_lock(a_lock)
{
    m_lock.Lock();
}

inline Locker::~Locker()
{
    m_lock.UnLock();
}

} //advcpp

#endif //LOCKER_HPP