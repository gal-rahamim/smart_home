#ifndef I_AGENT_CONTROLLER_HPP
#define I_AGENT_CONTROLLER_HPP

#include <vector>
#include "abc_publisher_agent.hpp"
#include "abc_subscriber_agent.hpp"

namespace smart_home{

class IAgentController {
public:
    typedef std::vector<std::tr1::shared_ptr<ABCPublisherAgent> > SensorsCont;
    typedef std::vector<std::tr1::shared_ptr<ABCSubscriberAgent> > ControllerCont;

public:
    virtual ~IAgentController();

    virtual void InitAll() = 0;
    virtual void GetAllSensors(SensorsCont& a_resAgents) = 0;
    virtual void GetAllControllers(ControllerCont& a_resAgents) = 0;
};

inline IAgentController::~IAgentController(){}

} //smart_home

#endif //I_AGENT_CONTROLLER_HPP