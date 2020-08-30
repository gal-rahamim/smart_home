#include "router.hpp"

namespace smart_home {

Router::Router(IAgentController& a_controller, ISubscriptionLocator& a_locator
            , IDequeuer& a_dequeuer, IEventDistributor& a_distributor)
: m_controller(a_controller)
, m_locator(a_locator)
, m_dequeuer(a_dequeuer)
, m_distributor(a_distributor)
{
    m_controller.InitAll();
    m_distributor.Init();
}            

void Router::Monitor(size_t a_numOfEvents)
{
    for(size_t i = 0 ; i < a_numOfEvents ; ++i) {
        Event event;
        m_dequeuer.Dequeue(event);
        ISubscriptionLocator::HandlingAgents agents;
        m_locator.FindAgents(event, agents);
        if(agents.size())
            m_distributor.Distribute(event, agents);
    }
}

} //smart_home
