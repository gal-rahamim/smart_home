#include <algorithm> 
#include <iostream>
#include "event_distributor_mt.hpp"

namespace smart_home {

struct Executer : public advcpp::Runnable {
    typedef std::tr1::shared_ptr<advcpp::Runnable> RunnablePtr;
    std::tr1::shared_ptr<advcpp::UnboundedWaitableQueue<RunnablePtr> > m_queue;
    advcpp::AtomicValue<size_t>& m_flag;

    Executer(std::tr1::shared_ptr<advcpp::UnboundedWaitableQueue<RunnablePtr> > a_queue, advcpp::AtomicValue<size_t>& a_flag)
    : m_queue(a_queue)
    , m_flag(a_flag)
    {}

    virtual void Run() {
        while(m_flag.Value() == 0) {
            RunnablePtr p;
            m_queue->Dequeue(p);
            if(m_flag.Value() == 0) {
                p->Run();
            }
        }
    }

};

EventDistributorMt::EventDistributorMt(IAgentController& a_agentController)
: m_agentController(a_agentController)
, m_threads()
, m_controllers()
, m_queues()
, m_flag()
{
}

EventDistributorMt::~EventDistributorMt()
{
    for(size_t i = 0 ; i < m_controllers.size() ; ++i)
    {
        m_queues[i]->WaitForQueueToEmpty();
    }
    ++m_flag;
    for(size_t i = 0 ; i < m_controllers.size() ; ++i) {
        m_queues[i]->SafeShutdown();
        m_threads[i]->Join();
    }
}

void EventDistributorMt::Init()
{
    m_agentController.GetAllControllers(m_controllers);

    for(size_t i = 0 ; i < m_controllers.size() ; ++i) {
        std::tr1::shared_ptr<advcpp::UnboundedWaitableQueue<RunnablePtr> > q(new advcpp::UnboundedWaitableQueue<RunnablePtr>);
        m_queues.push_back(q);
        std::tr1::shared_ptr<Executer> ex(new Executer(q, m_flag));
        std::tr1::shared_ptr<experis::Thread> t(new experis::Thread(ex));
        m_threads.push_back(t);
    }
}

void EventDistributorMt::Distribute(const Event& a_event, HandlingAgents& a_agents)
{
    for(size_t i = 0 ; i < a_agents.size() ; ++i){
        std::tr1::shared_ptr<advcpp::RunabbleTemplateMemFunc1constRefArg<ABCSubscriberAgent, Event> > runnableHandler
                    (new advcpp::RunabbleTemplateMemFunc1constRefArg<ABCSubscriberAgent, Event>(*a_agents[i], &ABCSubscriberAgent::Handle, a_event));
        for(size_t j = 0 ; j < m_controllers.size() ; ++j) {
            if(a_agents[i] == m_controllers[j]) {
                m_queues[j]->Enqueue(runnableHandler);
            }
        }
    }
}

} //smart_home
