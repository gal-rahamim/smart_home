#ifndef I_ENQUEUER_HPP
#define I_ENQUEUER_HPP

#include "event.hpp"

namespace smart_home {

class IEnqueuer {
public:
    virtual ~IEnqueuer();
    virtual void Enqueue(const Event& a_event) = 0;

};

inline IEnqueuer::~IEnqueuer(){}

} //smart_home

#endif //I_ENQUEUER_HPP