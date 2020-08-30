#include <algorithm>
#include "subscription_table.hpp"
#include "locker.hpp"

namespace smart_home {

struct KeyComp {
    bool operator()(std::pair<Event::Floor, Event::Room>& a, std::pair<Event::Floor, Event::Room>& b) const
    {
        return (a.first == b.first && a.second == b.second)
                || (a.first == b.first && b.second == "*")  
                || (b.first == "*" && b.second == "*");
    }
};

void SubsriptionTable::Add(std::tr1::shared_ptr<ABCSubscriberAgent> a_agent, const Event::Type& a_type,
                 const Event::Floor& a_floor, const Event::Room& a_room)
{
    advcpp::Locker guard(m_lock);
    m_map.insert(std::make_pair(a_type, std::make_pair(std::make_pair(a_floor, a_room), a_agent)));
}

void SubsriptionTable::Find(const Event::Type& a_type, const Event::Floor& a_floor,
                 const Event::Room& a_room, HandlingAgents& a_resAgents)
{
    advcpp::Locker guard(m_lock);
    KeyComp compare;
    std::pair<Event::Floor, Event::Room> tofind = std::make_pair(a_floor, a_room);
    std::pair<MultiMap::iterator, MultiMap::iterator> res = m_map.equal_range(a_type);
    for(MultiMap::iterator it = res.first; it != res.second ; ++it) {
        if(compare(it->second.first, tofind)){  
            a_resAgents.push_back(it->second.second);        
        }
    }
    
}

// void SubsriptionTable::Add(ABCSubscriberAgent* a_agent, const Event::Type& a_type
//                             , const Event::Location& a_location)
// {
//     advcpp::Locker guard(m_lock);
//     m_map.insert(std::make_pair(std::make_pair(a_type, a_location), a_agent));
// }

// void SubsriptionTable::Find(const Event::Type& a_type, const Event::Location& a_location
//                                     , HandlingAgents& a_resAgents)
// {
//     Key tofind = std::make_pair(a_type, a_location);
//     advcpp::Locker guard(m_lock);
//     MultiMap::iterator iter = m_map.find(tofind);
//     if(iter != m_map.end()) {
//         do {
//             a_resAgents.push_back(iter->second);
//             ++iter;
//         }
//         while(iter != m_map.end() && iter->first == tofind);
//     }
// }

} //smart_home