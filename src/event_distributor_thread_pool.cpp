#include <algorithm> 
#include "event_distributor_thread_pool.hpp"

namespace smart_home {


namespace details {

struct PushToPool {
    advcpp::ThreadPool& m_pool;
    const Event& m_event;
    PushToPool(advcpp::ThreadPool& a_pool, const Event& a_event)
    : m_pool(a_pool)
    , m_event(a_event){}

    void operator()(ABCSubscriberAgent* a_agent) const
    {
        advcpp::SharedPtr<advcpp::RunabbleTemplateMemFunc1constRefArg<ABCSubscriberAgent, Event> > runnableHandler
                    (new advcpp::RunabbleTemplateMemFunc1constRefArg<ABCSubscriberAgent, Event>(*a_agent, &ABCSubscriberAgent::Handle, m_event));
        m_pool.Submit(runnableHandler);
    }
};

} //details

EventDistributorThreadPool::EventDistributorThreadPool(size_t a_numOfThreads, size_t a_poolSize)
: m_threadPool(a_numOfThreads, a_poolSize)
{}

void EventDistributorThreadPool::Distribute(const Event& a_event, HandlingAgents a_agents) const
{
    std::for_each(a_agents.begin(), a_agents.end(), details::PushToPool(m_threadPool, a_event));
}

} //smart_home
