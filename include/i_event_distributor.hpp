#ifndef I_EVENT_DISTRIBUTOR_HPP
#define I_EVENT_DISTRIBUTOR_HPP

#include <tr1/memory>
#include <vector> 
#include "abc_subscriber_agent.hpp"
#include "event.hpp"

namespace smart_home {

class IEventDistributor {
public:
    typedef std::vector<std::tr1::shared_ptr<ABCSubscriberAgent> > HandlingAgents;

public:
    virtual ~IEventDistributor();

    virtual void Distribute(const Event& a_event, HandlingAgents& a_agents) = 0;
    virtual void Init() = 0;
};

inline IEventDistributor::~IEventDistributor(){}

} //smart_home

#endif //I_EVENT_DISTRIBUTOR_HPP