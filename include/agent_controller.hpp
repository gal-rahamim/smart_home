#ifndef AGENT_CONTROLLER_HPP
#define AGENT_CONTROLLER_HPP

#include <tr1/memory>
#include "i_agent.hpp"
#include "i_agent_controller.hpp"
#include "i_agent_loader.hpp"
#include "i_enqueuer.hpp"
#include "i_event_enroller.hpp"

namespace smart_home{

class AgentController : public IAgentController {
public:
    typedef std::vector<std::tr1::shared_ptr<ABCPublisherAgent> > SensorsCont;
    typedef std::vector<std::tr1::shared_ptr<ABCSubscriberAgent> > ControllerCont;

public:
    AgentController(IAgentLoader& a_loader, IEnqueuer& a_enqueuer, IEventEnroller& a_enroller);
    // ~AgentController();

    virtual void InitAll();
    virtual void GetAllSensors(SensorsCont& a_resAgents);
    virtual void GetAllControllers(ControllerCont& a_resAgents);

private:
    typedef std::vector<std::tr1::shared_ptr<IAgent> > AgentPtrCont;

private:
    IAgentLoader& m_loader;
    IEnqueuer& m_enqueuer;
    IEventEnroller& m_enroller;
    AgentPtrCont m_agents;
    SensorsCont m_sensors;
    ControllerCont m_controllers;
};

} //smart_home

#endif //AGENT_CONTROLLER_HPP