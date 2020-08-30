#ifndef MUTEX_EXCEPTIONS_HPP
#define MUTEX_EXCEPTIONS_HPP

#include <exception>

namespace experis {

class MutexInsufficientResources : private std::exception {
    virtual const char* what() const throw() {return "Insufficient resources to create Mutex\n";}
};

class MutexInsufficientMemory : private std::exception {
    virtual const char* what() const throw() {return "Insufficient memory to create Mutex\n";}
};

class MutexPremissionUnmatch : private std::exception {
    virtual const char* what() const throw() {return "Invalid premissions to create the Mutex\n";}
};

class MutexDestoryingBusyMutex : private std::exception {
    virtual const char* what() const throw() {return "Trying to destroy a busy Mutex\n";}
};

class MutexMaxNumRecursiveLocks : private std::exception {
    virtual const char* what() const throw() {return "Maximum number of recursive locks allready accuired\n";}
};

class MutexAllreadyLocked : private std::exception {
    virtual const char* what() const throw() {return "Trying to lock a locked Mutex\n";}
};

class MutexLockedByOtherThread : private std::exception {
    virtual const char* what() const throw() {return "Mutex is locked by other thread\n";}
};

class MutexAllreadyUnlocked : private std::exception {
    virtual const char* what() const throw() {return "Trying to unlock an unlocked Mutex\n";}
};

} //experis

#endif //MUTEX_EXCEPTIONS_HPP
