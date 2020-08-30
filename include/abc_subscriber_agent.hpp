#ifndef ABC_SUBSCRIBER_AGENT_HPP
#define ABC_SUBSCRIBER_AGENT_HPP

#include "i_event_enroller.hpp"
#include "i_agent.hpp"
#include "event.hpp"
#include "atomic_value.hpp"

namespace smart_home{

class ABCSubscriberAgent : public IAgent {
public:
    virtual ~ABCSubscriberAgent();

    void SetEnroller(IEventEnroller* a_eventEnroller);
    void Subscribe(std::tr1::shared_ptr<ABCSubscriberAgent> a_agentSPtr, const Event::Type& a_type, const Event::Floor& a_floor, const Event::Room& a_room);
    virtual void Init(const Id& a_id, const Type& a_type, const Floor& a_floor, const Room& a_room
            , const Log& a_log = "", const Config& a_config = "") = 0;
    virtual void Handle(const Event& a_event) = 0;
    virtual void Work() = 0;
    size_t GetNumOfSubscriptions();

private:
    IEventEnroller* m_eventEnroller;        
    advcpp::AtomicValue<size_t> m_numOfSubscriptions;
};

} //smart_home

#include "inl/abc_subscriber_agent.hxx"

#endif //ABC_SUBSCRIBER_AGENT_HPP