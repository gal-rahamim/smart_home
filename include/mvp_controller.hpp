#ifndef MVP_CONTROLLER_HPP
#define MVP_CONTROLLER_HPP

#include <tr1/memory>
#include <vector>
#include <cassert>
#include "abc_subscriber_agent.hpp"
#include "mutex.hpp"
#include "locker.hpp"

namespace smart_home {

class MvpController : public ABCSubscriberAgent, public std::tr1::enable_shared_from_this<MvpController> {
public:
    typedef std::vector<std::pair<Floor, Room> > SubParams;
public:
    MvpController();
    MvpController(const SubParams& a_paramsToSub);
    ~MvpController();
    virtual void Init(const Id& a_id, const Type& a_type, const Floor& a_floor, const Room& a_room
        , const Log& a_log = "", const Config& a_config = "");
    virtual void Handle(const Event& a_event);
    virtual void Work();
    size_t EventsRecieved() const;

private:
    Type m_type;
    SubParams m_paramsToSub;
    size_t m_numEventsRecieved;
    size_t m_numEventsToRecieve;
    std::vector<int> m_payload;
    mutable experis::Mutex m_lock;
};

} //smart_home

#endif //MVP_CONTROLLER_HPP