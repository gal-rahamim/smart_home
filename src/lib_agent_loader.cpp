#include "lib_agent_loader.hpp"

namespace smart_home {

void LibAgentLoader::Load(AgentPtrCont& a_resAgentCont)
{
    std::tr1::shared_ptr<IAgent> newSensor1(m_factory.GetObject("mvp_sensor"));
    newSensor1->Init("", "temprature", "floor_1", "room_a", "", "10000");
    a_resAgentCont.push_back(newSensor1);
    // m_sensors.push_back(dynamic_cast<MvpSensor*>(newSensor1.get()));

    std::tr1::shared_ptr<IAgent> newSensor2(m_factory.GetObject("mvp_sensor"));
    newSensor2->Init("", "temprature", "floor_1", "room_b", "", "10000");
    a_resAgentCont.push_back(newSensor2);
    // m_sensors.push_back(dynamic_cast<MvpSensor*>(newSensor2.get()));

    std::tr1::shared_ptr<IAgent> newController1(m_factory.GetObject("mvp_controller"));
    newController1->Init("", "temprature", "floor_1", "room_a", "", "10000");
    a_resAgentCont.push_back(newController1);
    // m_controllers.push_back(dynamic_cast<MvpController*>(newController1.get()));

    std::tr1::shared_ptr<IAgent> newController2(m_factory.GetObject("mvp_controller"));
    newController2->Init("", "temprature", "floor_1", "room_b", "", "10000");
    a_resAgentCont.push_back(newController2);
    // m_controllers.push_back(dynamic_cast<MvpController*>(newController2.get()));

}

} //smart_home