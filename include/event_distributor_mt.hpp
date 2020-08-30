#ifndef EVENT_DISTRIBUTOR_MT_HPP
#define EVENT_DISTRIBUTOR_MT_HPP

#include "i_event_distributor.hpp"
#include "unbounded_waitable_queue.hpp"
#include "common.hpp"
#include "thread_group.hpp"
#include "atomic_value.hpp"
#include "i_agent_controller.hpp"

namespace smart_home {

class EventDistributorMt : public IEventDistributor {
public:
    EventDistributorMt(IAgentController& a_agentController);
    ~EventDistributorMt();

    virtual void Distribute(const Event& a_event, HandlingAgents& a_agents);
    virtual void Init();

private:
    typedef std::tr1::shared_ptr<advcpp::Runnable> RunnablePtr;
    typedef std::vector<std::tr1::shared_ptr<ABCSubscriberAgent> > ControllersCont;
    typedef std::vector<std::tr1::shared_ptr<experis::Thread> > ThreadsCont;
    typedef std::vector<std::tr1::shared_ptr<advcpp::UnboundedWaitableQueue<RunnablePtr> > > QueuesCont;

private:
    IAgentController& m_agentController;
    ThreadsCont m_threads;
    ControllersCont m_controllers;
    QueuesCont m_queues;
    advcpp::AtomicValue<size_t> m_flag;
};

} //smart_home

#endif //EVENT_DISTRIBUTOR_MT_HPP