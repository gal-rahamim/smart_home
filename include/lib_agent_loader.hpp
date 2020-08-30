#ifndef LIB_AGENT_LOADER_HPP
#define LIB_AGENT_LOADER_HPP

#include <tr1/memory>
#include "i_agent_loader.hpp"
#include "object_factory.hpp"
#include "mvp_controller.hpp"
#include "mvp_sensor.hpp"

namespace smart_home {

class LibAgentLoader : public IAgentLoader {
public:
    typedef std::vector<std::tr1::shared_ptr<IAgent> > AgentPtrCont;

public:
    virtual void Load(AgentPtrCont& a_resAgentCont);
    void GetControllers(std::vector<MvpController*>& a_controllers);

private:
    advcpp::ObjectFactory<std::tr1::shared_ptr<IAgent> > m_factory;
    std::vector<MvpSensor*> m_sensors;
    std::vector<MvpController*> m_controllers;
};

inline void LibAgentLoader::GetControllers(std::vector<MvpController*>& a_controllers)
{
    a_controllers = m_controllers;
}

} //smart_home

#endif //LIB_AGENT_LOADER_HPP