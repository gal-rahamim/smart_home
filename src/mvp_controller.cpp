#include <cstdlib>
#include "mvp_controller.hpp"

namespace smart_home{

namespace mvp_controller_detail {
struct KeyComp {
    bool operator()(std::pair<MvpController::Floor, MvpController::Room>& a, std::pair<MvpController::Floor, MvpController::Room>& b) const
    {
        return (a.first == b.first && a.second == b.second)
                || (a.first == b.first && b.second == "*")  
                || (b.first == "*" && b.second == "*");
    }
};
} //mvp_controller_detail 

MvpController::MvpController()
: m_type()
, m_paramsToSub()
, m_numEventsRecieved(0)
, m_numEventsToRecieve(0)
, m_payload(2, 0)
, m_lock()
{}

MvpController::MvpController(const SubParams& a_paramsToSub)
: m_type()
, m_paramsToSub(a_paramsToSub)
, m_numEventsRecieved(0)
, m_payload(2, 0)
, m_lock()
{}

MvpController::~MvpController()
{
    assert(m_numEventsRecieved == m_numEventsToRecieve);
}

void MvpController::Init(const Id& a_id, const Type& a_type, const Floor& a_floor, const Room& a_room
        , const Log& a_log, const Config& a_config)
{
    m_type = a_type;
    m_paramsToSub.push_back(std::make_pair(a_floor, a_room));
    if(a_config != "") {
        m_numEventsToRecieve = atoi(a_config.c_str());
    }
}

void MvpController::Handle(const Event& a_event)
{
    advcpp::Locker guard(m_lock);
    ++m_numEventsRecieved;
    std::pair<Floor, Room> toFind = std::make_pair(a_event.GetFloor(), a_event.GetRoom());
    mvp_controller_detail::KeyComp compare;
    for(size_t i = 0 ; i < m_paramsToSub.size() ; ++i) {
        if(compare(toFind, m_paramsToSub[i])) {
            int newItem = atoi(a_event.GetPayload().c_str());
            assert(m_payload[i] == newItem);
            ++m_payload[i];
        }
    }
}

void MvpController::Work() 
{
    std::tr1::shared_ptr<ABCSubscriberAgent> me = shared_from_this();
    for(size_t i = 0 ; i < m_paramsToSub.size() ; ++i) {
        Subscribe(me, m_type, m_paramsToSub[i].first, m_paramsToSub[i].second);
    }
}

size_t MvpController::EventsRecieved() const
{
    advcpp::Locker guard(m_lock);
    return m_numEventsRecieved;
}

extern "C"
std::tr1::shared_ptr<IAgent> CreateObject()
{
    return std::tr1::shared_ptr<IAgent>(new MvpController);
}

} //smart_home