#include <cerrno>
#include <assert.h>
#include "semaphore.hpp"
#include "semaphore_exceptions.hpp"

namespace experis {
Semaphore::Semaphore(size_t _size) {
    if(0 != sem_init(&m_sem, 0, _size)) {
        assert(errno != ENOSYS);
        assert(errno != EINVAL);
        assert(!"sem_init failed");
    }
}

Semaphore::~Semaphore() {
    if(0 != sem_destroy(&m_sem)) {
        assert(errno != EINVAL);
        assert(!"sem_destroy failed");
    }
}

void Semaphore::Post() {
    if(0 != sem_post(&m_sem)) {
        assert(errno != EINVAL);
        if(errno == EOVERFLOW) {
            throw SemaphoreOverFlow();
        }
        else {
            assert(!"sem_post failed");
        }
    }
}

void Semaphore::Wait() {
    if(0 != sem_wait(&m_sem)) {
        assert(errno != EINVAL);
        assert(errno != EINTR);
        assert(errno != EAGAIN);
        assert(errno != ETIMEDOUT);
        assert(!"sem_wait failed");
    }
}

} //experis
