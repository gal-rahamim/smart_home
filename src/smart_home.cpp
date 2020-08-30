#include "smart_home.hpp"

namespace smart_home {

SmartHome::SmartHome()
: m_eventQueue()
, m_enq(m_eventQueue)
, m_deq(m_eventQueue)
, m_agentLoader()
, m_table()
, m_enroller(m_table)
, m_agentController(m_agentLoader, m_enq, m_enroller)
, m_distributor(m_agentController)
, m_locator(m_table)
, m_router(m_agentController, m_locator, m_deq, m_distributor)
{}

void SmartHome::Start(size_t a_numOfEvents)
{
    m_router.Monitor(a_numOfEvents*2);
}

} //smart_home