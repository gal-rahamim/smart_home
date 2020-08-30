#include "mu_test.h"
#include <iostream>
#include <unistd.h>
#include <tr1/memory>
#include <assert.h>
#include "router.hpp"
#include "unbounded_waitable_queue.hpp"
#include "dequeuer.hpp"
#include "enqueuer.hpp"
#include "event_distributor.hpp"
#include "event_distributor_mt.hpp"
#include "event_enroller.hpp"
#include "agent_controller.hpp"
#include "subscription_table.hpp"
#include "mvp_agent_loader.hpp"
#include "subscription_locator.hpp"
#include "common.hpp"
#include "thread.hpp"

using namespace smart_home;
using namespace advcpp;
using namespace experis;
using namespace std::tr1;

UNIT(two_sensors_three_controllers)
    //---------init variables--------------
    const size_t N = 10000, numSensors = 2;
    UnboundedWaitableQueue<Event> eventQueue;
    Enqueuer enq(eventQueue);
    Dequeuer deq(eventQueue);
    EventDistributor distributor;
    SubsriptionTable table;
    EventEnroller enroller(table);
    MvpAgentLoader agentLoader(N);
    AgentController agentController(agentLoader, enq, enroller);
    SubscriptionLocator locator(table);
    Router smartHome(agentController, locator, deq, distributor);

    //---------run smart home thread-----------
    shared_ptr<RunabbleTemplateMemFunc1Arg<Router, size_t> > 
        runableMonitor(new RunabbleTemplateMemFunc1Arg<Router, size_t>
                        (smartHome, &Router::Monitor, N*numSensors));
    Thread smartHomeThread(runableMonitor);

    //--------Join threads -----------
    smartHomeThread.Join();

    //-------- Verify results ----------
    std::vector<shared_ptr<MvpController> > controllers;
    agentLoader.GetControllers(controllers);
    ASSERT_EQUAL_INT(controllers[0]->EventsRecieved(), N*2);
    ASSERT_EQUAL_INT(controllers[1]->EventsRecieved(), N);
    ASSERT_EQUAL_INT(controllers[2]->EventsRecieved(), N);

END_UNIT

UNIT(two_sensors_three_controllers_mt)
    //---------init variables--------------
    const size_t N = 10000, numSensors = 2, numOfThreads = 3;
    UnboundedWaitableQueue<Event> eventQueue;
    Enqueuer enq(eventQueue);
    Dequeuer deq(eventQueue);
    EventDistributorMt distributor(numOfThreads);
    SubsriptionTable table;
    EventEnroller enroller(table);
    MvpAgentLoader agentLoader(N);
    AgentController agentController(agentLoader, enq, enroller);
    SubscriptionLocator locator(table);
    Router smartHome(agentController, locator, deq, distributor);

    smartHome.Monitor(N*numSensors);

    std::vector<shared_ptr<MvpController> > controllers;
    agentLoader.GetControllers(controllers);
    usleep(10);
    ASSERT_EQUAL_INT(controllers[0]->EventsRecieved(), N*2);
    ASSERT_EQUAL_INT(controllers[1]->EventsRecieved(), N);
    ASSERT_EQUAL_INT(controllers[2]->EventsRecieved(), N);
END_UNIT

TEST_SUITE(smart_home_mvp_0)
    TEST(two_sensors_three_controllers)
    TEST(two_sensors_three_controllers_mt)

END_SUITE

