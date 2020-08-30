#include <assert.h>
#include <errno.h>
#include "mutex.hpp"
#include "mutex_exceptions.hpp"

namespace experis {

Mutex::Mutex() {
    int result = pthread_mutex_init(&m_mutex, NULL);
    if(0 != result) {
        assert(result != EBUSY);
        assert(result != EINVAL);
        if(result == EAGAIN) {
            throw MutexInsufficientResources();
        }
        else if(result == ENOMEM){
            throw MutexInsufficientMemory();
        }
        else if(result == EPERM) {
            throw MutexPremissionUnmatch();
        }
        else {
            assert(!"pthread_mutex_init failed");
        }
    }
}

Mutex::~Mutex() {
    int result = pthread_mutex_destroy(&m_mutex);
    if(0 != result) {
        assert(result != EINVAL);
        assert(result != EBUSY);
        assert(!"pthread_mutex_destroy failed");
    }
}

void Mutex::Lock() const {
    int result = pthread_mutex_lock(&m_mutex);
    if(0 != result) {
        assert(result != EINVAL);
        assert(result != EAGAIN);
        assert(result != EDEADLK);
        assert(!"pthread_mutex_lock failed");
    }
}

void Mutex::UnLock() const {
    int result = pthread_mutex_unlock(&m_mutex);
    if(0 != result) {
        assert(result != EINVAL);
        if(result == EPERM) {
            throw MutexLockedByOtherThread();
        }
        else if(result == EDEADLK) {
            throw MutexAllreadyUnlocked();
        }
        else {
            assert(!"pthread_mutex_unlock failed");
        }
    }
}

} //experis
