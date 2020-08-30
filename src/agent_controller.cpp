#include <algorithm>
#include <cassert>
#include "agent_controller.hpp"
#include "abc_publisher_agent.hpp"
#include "abc_subscriber_agent.hpp"

namespace smart_home {

AgentController::AgentController(IAgentLoader& a_loader, IEnqueuer& a_enqueuer, IEventEnroller& a_enroller)
: m_loader(a_loader)
, m_enqueuer(a_enqueuer)
, m_enroller(a_enroller)
, m_sensors()
, m_controllers()
{
    m_loader.Load(m_agents);
}

namespace details {

struct DispatchAPI {
    IEnqueuer* m_enqueuer;
    IEventEnroller* m_enroller;
    AgentController::SensorsCont& m_sensors;
    AgentController::ControllerCont& m_controllers;

    DispatchAPI(IEnqueuer* a_enqueuer, IEventEnroller* a_enroller, AgentController::SensorsCont& a_sensors
                , AgentController::ControllerCont& a_controllers)
    : m_enqueuer(a_enqueuer)
    , m_enroller(a_enroller)
    , m_sensors(a_sensors)
    , m_controllers(a_controllers)
    {}

    void operator()(std::tr1::shared_ptr<IAgent> a_agent)
    {
        int n = 0;
        std::tr1::shared_ptr<ABCSubscriberAgent> subAgent = std::tr1::dynamic_pointer_cast<ABCSubscriberAgent>(a_agent);        
        if(subAgent) {
            subAgent->SetEnroller(m_enroller);
            subAgent->Work();            
            ++n;
            m_controllers.push_back(subAgent);
        }
    
        std::tr1::shared_ptr<ABCPublisherAgent> pubAgent = std::tr1::dynamic_pointer_cast<ABCPublisherAgent>(a_agent);
        if(pubAgent) {
            pubAgent->SetEnqueuer(m_enqueuer);
            pubAgent->Start();
            ++n;
            m_sensors.push_back(pubAgent);
        }

        assert(n > 0 && "Panic!! Invalid Agent!!");        
    }
};

} //details

void AgentController::InitAll()
{
    std::for_each(m_agents.begin(), m_agents.end(), details::DispatchAPI(&m_enqueuer, &m_enroller, m_sensors, m_controllers));
}

void AgentController::GetAllSensors(SensorsCont& a_resAgents)
{
    a_resAgents = m_sensors;
}

void AgentController::GetAllControllers(ControllerCont& a_resAgents)
{
    a_resAgents = m_controllers;
}

} //smart_home