#include <tr1/memory>
#include <sstream> 
#include <vector>
#include "mvp_agent_loader.hpp"
#include "common.hpp"

namespace smart_home {

MvpSensor* MvpSensorFactory(size_t a_numOfEvents)
{
    return new MvpSensor(a_numOfEvents);
}

MvpController* MvpControllerFactory1()
{
    std::vector<std::pair<std::string, std::string> > subParms;
    subParms.push_back(std::make_pair("floor_1", "room_a"));
    subParms.push_back(std::make_pair("floor_1", "room_b"));
    return new MvpController(subParms);
}

MvpController* MvpControllerFactory2()
{
    std::vector<std::pair<std::string, std::string> > subParms;
    subParms.push_back(std::make_pair("floor_1", "room_a"));
    return new MvpController(subParms);
}

MvpController* MvpControllerFactory3()
{
    std::vector<std::pair<std::string, std::string> > subParms;
    subParms.push_back(std::make_pair("floor_1", "room_b"));
    return new MvpController(subParms);
}

void MvpAgentLoader::Load(AgentPtrCont& a_resAgentCont)
{
    std::tr1::shared_ptr<MvpSensor> newSensor1(MvpSensorFactory(m_numOfEventsPerSensor));
    newSensor1->Init("", "temprature", "floor_1", "room_a");
    a_resAgentCont.push_back(newSensor1);
    m_sensors.push_back(newSensor1);

    std::tr1::shared_ptr<MvpSensor> newSensor2(MvpSensorFactory(m_numOfEventsPerSensor));
    newSensor2->Init("", "temprature", "floor_1", "room_b");
    a_resAgentCont.push_back(newSensor2);
    m_sensors.push_back(newSensor2);

    std::tr1::shared_ptr<MvpController> newController1(MvpControllerFactory1());
    newController1->Init("", "temprature", "", "");
    a_resAgentCont.push_back(newController1);
    m_controllers.push_back(newController1);
    
    std::tr1::shared_ptr<MvpController> newController2(MvpControllerFactory2());
    newController2->Init("", "temprature", "", "");
    a_resAgentCont.push_back(newController2);
    m_controllers.push_back(newController2);

    std::tr1::shared_ptr<MvpController> newController3(MvpControllerFactory3());
    newController3->Init("", "temprature", "", "");
    a_resAgentCont.push_back(newController3);
    m_controllers.push_back(newController3);
}

} //smart_home