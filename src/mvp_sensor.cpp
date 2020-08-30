#include <sstream>
#include <cstdlib>
#include "mvp_sensor.hpp"

namespace smart_home {

struct PublishNEvents : public advcpp::Runnable {
    ABCPublisherAgent* m_sensor;
    size_t m_num;
    const std::string& m_type;
    const std::string& m_floor;
    const std::string& m_room;
    PublishNEvents(ABCPublisherAgent* a_sensor, size_t a_num, const std::string& a_type, const std::string& a_floor, const std::string& a_room)
    : m_sensor(a_sensor)
    , m_num(a_num)
    , m_type(a_type)
    , m_floor(a_floor)
    , m_room(a_room)
    {}
    virtual void Run() 
    {
        for( size_t i = 0 ; i < m_num ; ++i) {
            std::stringstream s;
            s << i;
            Event e(m_type, m_floor, m_room, s.str());
            m_sensor->Publish(e);
        }
    }
};

MvpSensor::MvpSensor()
: m_id()
, m_type()
, m_floor()
, m_room()
, m_numOfEvents(0)
{}

MvpSensor::MvpSensor(size_t a_numOfEvents)
: m_id()
, m_type()
, m_floor()
, m_room()
, m_numOfEvents(a_numOfEvents)
{}

MvpSensor::~MvpSensor() {}

void MvpSensor::Init(const Id& a_id, const Type& a_type, const Floor& a_floor, const Room& a_room
        , const Log& a_log, const Config& a_config)
{
    m_id = a_id;
    m_type = a_type;
    m_floor = a_floor;
    m_room = a_room;
    if(a_config != ""){
        m_numOfEvents = atoi(a_config.c_str());
    }
}

void MvpSensor::Work()
{
    for( size_t i = 0 ; i < m_numOfEvents ; ++i) {
        std::stringstream s;
        s << i;
        Event e(m_type, m_floor, m_room, s.str());
        Publish(e);
    }
}

extern "C"
std::tr1::shared_ptr<IAgent> CreateObject()
{
    return std::tr1::shared_ptr<IAgent>(new MvpSensor);
}

} //smart_home