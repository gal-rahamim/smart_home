#ifndef MVP_AGENT_LOADER_HPP
#define MVP_AGENT_LOADER_HPP

#include <iostream>
#include <string>
#include "i_agent_loader.hpp"
#include "mvp_sensor.hpp"
#include "mvp_controller.hpp"

namespace smart_home {

class MvpAgentLoader : public IAgentLoader {
public:
    MvpAgentLoader(size_t a_numOfEventsPerSensor);
    virtual void Load(AgentPtrCont& a_resAgentCont);

    void GetControllers(std::vector<std::tr1::shared_ptr<MvpController> >& a_controllers);

private:
    size_t m_numOfEventsPerSensor;
    std::vector<std::tr1::shared_ptr<MvpSensor> > m_sensors;
    std::vector<std::tr1::shared_ptr<MvpController> > m_controllers;
};

inline MvpAgentLoader::MvpAgentLoader(size_t a_numOfEventsPerSensor)
: m_numOfEventsPerSensor(a_numOfEventsPerSensor)
, m_sensors()
, m_controllers()
{}

inline void MvpAgentLoader::GetControllers(std::vector<std::tr1::shared_ptr<MvpController> >& a_controllers)
{
    a_controllers = m_controllers;
}

} //smart_home

#endif //MVP_AGENT_LOADER_HPP