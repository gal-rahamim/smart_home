#ifndef EVENT_DISTRIBUTOR_HPP
#define EVENT_DISTRIBUTOR_HPP

#include "i_event_distributor.hpp"

namespace smart_home {

class EventDistributor : public IEventDistributor {
public:
    virtual void Distribute(const Event& a_event, HandlingAgents a_agents);
};

} //smart_home

#endif //EVENT_DISTRIBUTOR_HPP