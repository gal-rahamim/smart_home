#ifndef ROUTER_HPP
#define ROUTER_HPP

#include "i_agent_controller.hpp"
#include "i_subscription_locator.hpp"
#include "i_dequeuer.hpp"
#include "i_event_distributor.hpp"

namespace smart_home {

class Router {
public:
    Router(IAgentController& a_controller, ISubscriptionLocator& a_locator
            , IDequeuer& a_dequeuer, IEventDistributor& a_distributor);    

    void Monitor(size_t a_numOfEvents);

private:
    IAgentController& m_controller;
    ISubscriptionLocator& m_locator;
    IDequeuer& m_dequeuer;
    IEventDistributor& m_distributor;    
};

} //smart_home

#endif //ROUTER_HPP