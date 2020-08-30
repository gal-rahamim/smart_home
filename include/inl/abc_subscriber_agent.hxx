#ifndef ABC_SUBSCRIBER_AGENT_HXX
#define ABC_SUBSCRIBER_AGENT_HXX

#include "abc_subscriber_agent.hpp"

namespace smart_home{

inline ABCSubscriberAgent::~ABCSubscriberAgent(){}

inline void ABCSubscriberAgent::SetEnroller(IEventEnroller* a_eventEnroller)
{
    m_eventEnroller = a_eventEnroller;
}

inline void ABCSubscriberAgent::Subscribe(std::tr1::shared_ptr<ABCSubscriberAgent> a_agentSPtr, const Event::Type& a_type, const Event::Floor& a_floor, const Event::Room& a_room)
{
    m_eventEnroller->Subscribe(a_agentSPtr, a_type, a_floor, a_room);
    ++m_numOfSubscriptions;
}

inline size_t ABCSubscriberAgent::GetNumOfSubscriptions()
{
    return m_numOfSubscriptions.Value();
}

} //smart_home


#endif //ABC_SUBSCRIBER_AGENT_HXX