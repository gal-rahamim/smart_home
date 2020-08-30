#ifndef I_DEQUEUER_HPP
#define I_DEQUEUER_HPP

#include "event.hpp"

namespace smart_home {

class IDequeuer {
public:
    virtual ~IDequeuer();
    virtual void Dequeue(Event& a_event) = 0;

};

inline IDequeuer::~IDequeuer(){}

} //smart_home

#endif //I_DEQUEUER_HPP