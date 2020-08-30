#ifndef SEMAPHORE_HPP
#define SEMAPHORE_HPP

#include <semaphore.h>

namespace experis {

class Semaphore {
public:
    Semaphore(size_t _size = 0);
    ~Semaphore();

    void Post();
    void Wait();
private:
    Semaphore(const Semaphore&); //no copy
    Semaphore& operator=(const Semaphore&); //no copy

    sem_t m_sem;
};

} //experis

#endif //SEMAPHORE_HPP
