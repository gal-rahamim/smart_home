#include "mu_test.h"
#include "smart_home.hpp"

using namespace smart_home;


UNIT(two_sensors_two_controllers_mt_from_lib)
    const size_t numOfEventsPerSensor = 10000;
    SmartHome smartHome;
    smartHome.Start(numOfEventsPerSensor);
    ASSERT_PASS();
END_UNIT

TEST_SUITE(smart_home_mvp_1)
    TEST(two_sensors_two_controllers_mt_from_lib)

END_SUITE

