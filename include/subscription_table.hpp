#ifndef SUBSCRIPTION_TABLE_HPP
#define SUBSCRIPTION_TABLE_HPP

#include <vector>
#include <map>
#include <tr1/memory>
#include "event.hpp"
#include "abc_subscriber_agent.hpp"
#include "mutex.hpp"

namespace smart_home {

class SubsriptionTable {
public:    
    typedef std::vector<std::tr1::shared_ptr<ABCSubscriberAgent> > HandlingAgents;

public:
    void Add(std::tr1::shared_ptr<ABCSubscriberAgent> a_agent, const Event::Type& a_type, const Event::Floor& a_floor, const Event::Room& a_room);        
    void Find(const Event::Type& a_type, const Event::Floor& a_floor, const Event::Room& a_room, HandlingAgents& a_resAgents);

private:
    // typedef std::pair<Event::Type, std::pair<Event::Floor, Event::Room> > Key;
    typedef std::multimap<Event::Type, std::pair<std::pair<Event::Floor, Event::Room>, std::tr1::shared_ptr<ABCSubscriberAgent> > > MultiMap;  

private:
    MultiMap m_map;
    experis::Mutex m_lock;
};

} //smart_home

#endif // SUBSCRIPTION_TABLE_HPP