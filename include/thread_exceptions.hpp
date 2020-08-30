#ifndef THREAD_EXCEPTIONS_HPP
#define THREAD_EXCEPTIONS_HPP

#include <exception>

namespace experis {

class ThreadInsufficientResources : private std::exception {
    virtual const char* what() const throw() {return "Insufficient resources to create Thread\n";}
};

class ThreadInvalidPremissions : private std::exception {
    virtual const char* what() const throw() {return "Invalid premissions to create the Thread\n";}
};

class ThreadJoiningEachOther : private std::exception {
    virtual const char* what() const throw() {return "Two threads trying to join each other\n";}
};

} //experis

#endif //THREAD_EXCEPTIONS_HPP
