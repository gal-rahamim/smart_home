#ifndef I_EVENT_ENROLLER_HPP
#define I_EVENT_ENROLLER_HPP

#include <tr1/memory>
#include "event.hpp"

namespace smart_home {

class ABCSubscriberAgent;

class IEventEnroller {
public: 
    virtual ~IEventEnroller();

    virtual void Subscribe(std::tr1::shared_ptr<ABCSubscriberAgent> a_agent, const Event::Type& a_type, const Event::Floor& a_floor, const Event::Room& a_room) = 0;

};

inline IEventEnroller::~IEventEnroller(){}

} //smart_home

#endif //I_EVENT_ENROLLER_HPP