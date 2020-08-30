#ifndef EVENT_DISTRIBUTOR_THREAD_POOL_HPP
#define EVENT_DISTRIBUTOR_THREAD_POOL_HPP

#include "i_event_distributor.hpp"
#include "thread_pool.hpp"

namespace smart_home {

class EventDistributorThreadPool : public IEventDistributor {
public:
    EventDistributorThreadPool(size_t a_numOfThreads, size_t a_poolSize = 128);
    virtual void Distribute(const Event& a_event, HandlingAgents a_agents) const;
private:
    mutable advcpp::ThreadPool m_threadPool;
};

} //smart_home

#endif //EVENT_DISTRIBUTOR_THREAD_POOL_HPP