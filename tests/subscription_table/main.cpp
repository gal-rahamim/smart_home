#include "mu_test.h"
#include <iostream>
#include <unistd.h>
#include <tr1/memory>
#include <assert.h>
#include "subscription_table.hpp"
#include "mvp_agent_loader.hpp"

using namespace smart_home;


UNIT(basic_add_find_test)
    SubsriptionTable table;
    ABCSubscriberAgent* agent1 = MvpControllerFactory();
    ABCSubscriberAgent* agent2 = MvpControllerFactory();
    ABCSubscriberAgent* agent3 = MvpControllerFactory();
    table.Add(agent1, "open_door", "floor_2", "room_a");
    table.Add(agent2, "lock_gate", "floor_0", "gate_1");
    table.Add(agent3, "open_door", "floor_2", "*");

    SubsriptionTable::HandlingAgents agentsPtrs;
    table.Find("open_door", "floor_2", "room_a", agentsPtrs);

    ASSERT_EQUAL_INT(agentsPtrs.size(), 1);
    ASSERT_THAT(agent1 == agentsPtrs[0]);

    agentsPtrs.clear();
    table.Find("open_door", "floor_2", "*", agentsPtrs);
    ASSERT_EQUAL_INT(agentsPtrs.size(), 2);
    ASSERT_THAT(agent1 == agentsPtrs[0]);
    ASSERT_THAT(agent3 == agentsPtrs[1]);

    delete agent1;
    delete agent2;
    delete agent3;

END_UNIT


TEST_SUITE(subsription_table_test)
    TEST(basic_add_find_test)

END_SUITE

