#ifndef SMART_HOME_HPP
#define SMART_HOME_HPP

#include "common.hpp"
#include "router.hpp"
#include "unbounded_waitable_queue.hpp"
#include "dequeuer.hpp"
#include "enqueuer.hpp"
#include "event_distributor.hpp"
#include "event_distributor_mt.hpp"
#include "event_enroller.hpp"
#include "agent_controller.hpp"
#include "subscription_table.hpp"
#include "subscription_locator.hpp"
#include "common.hpp"
#include "thread.hpp"
#include "lib_agent_loader.hpp"

namespace smart_home {

class SmartHome : private advcpp::UnCopyable {
public:
    SmartHome();
    void Start(size_t a_numOfEvents);

private:
    advcpp::UnboundedWaitableQueue<Event> m_eventQueue;
    Enqueuer m_enq;
    Dequeuer m_deq;
    LibAgentLoader m_agentLoader;
    SubsriptionTable m_table;
    EventEnroller m_enroller;
    AgentController m_agentController;
    EventDistributorMt m_distributor;
    SubscriptionLocator m_locator;
    Router m_router;
};

} //smart_home

#endif //SMART_HOME_HPP