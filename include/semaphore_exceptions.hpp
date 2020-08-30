#ifndef SEMAPHORE_EXCEPTIONS_HPP
#define SEMAPHORE_EXCEPTIONS_HPP

#include <exception>

namespace experis {

class SemaphoreTooBigSize : private std::exception {
    virtual const char* what() const throw() {return "Semaphore size recived was too big\n";}
};

class SemaphoreOverFlow : private std::exception {
    virtual const char* what() const throw() {return "Semaphore overflow\n";}
};

class SemaphoreBlocked : private std::exception {
    virtual const char* what() const throw() {return "Semaphore was blocked\n";}
};

class SemaphoreTimedOut : private std::exception {
    virtual const char* what() const throw() {return "Semaphore timedout\n";}
};

} //experis

#endif //SEMAPHORE_EXCEPTIONS_HPP
