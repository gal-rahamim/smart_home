#ifndef MVP_SENSOR_HPP
#define MVP_SENSOR_HPP

#include <tr1/memory>
#include "abc_publisher_agent.hpp"
#include "thread.hpp"

namespace smart_home {

class MvpSensor : public ABCPublisherAgent {
public:
    MvpSensor();
    MvpSensor(size_t a_numOfEvents);
    ~MvpSensor();
    virtual void Init(const Id& a_id, const Type& a_type, const Floor& a_floor, const Room& a_room
        , const Log& a_log = "", const Config& a_config = "");
    virtual void Work();

private:
    Id m_id;
    Type m_type;
    Floor m_floor;
    Room m_room;
    size_t m_numOfEvents;
};

} //smart_home

#endif //MVP_SENSOR_HPP