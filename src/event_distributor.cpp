#include <algorithm> 
#include "event_distributor.hpp"

namespace smart_home {


namespace details {

struct Handle {
    const Event& m_event;
    Handle(const Event& a_event)
    : m_event(a_event){}

    void operator()(std::tr1::shared_ptr<ABCSubscriberAgent> a_agent) const
    {
        a_agent->Handle(m_event);
    }
};

} //details

void EventDistributor::Distribute(const Event& a_event, HandlingAgents a_agents)
{
    std::for_each(a_agents.begin(), a_agents.end(), details::Handle(a_event));
}

} //smart_home
