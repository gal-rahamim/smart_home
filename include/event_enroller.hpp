#ifndef EVENT_ENROLLER_HPP
#define EVENT_ENROLLER_HPP

#include "i_event_enroller.hpp"
#include "subscription_table.hpp"

namespace smart_home {

class EventEnroller : public IEventEnroller {
public: 
    EventEnroller(SubsriptionTable& a_table);

    virtual void Subscribe(std::tr1::shared_ptr<ABCSubscriberAgent> a_agent, const Event::Type& a_type
                        , const Event::Floor& a_floor, const Event::Room& a_room);

private:
    SubsriptionTable& m_table;
};

inline EventEnroller::EventEnroller(SubsriptionTable& a_table)
: m_table(a_table)
{
}

inline void EventEnroller::Subscribe(std::tr1::shared_ptr<ABCSubscriberAgent> a_agent, const Event::Type& a_type
                        , const Event::Floor& a_floor, const Event::Room& a_room)
{
    m_table.Add(a_agent, a_type, a_floor, a_room);
}

} //smart_home

#endif //I_EVENT_ENROLLER_HPP