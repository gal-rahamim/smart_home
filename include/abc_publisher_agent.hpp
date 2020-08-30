#ifndef ABC_PUBLISHER_AGENT_HPP
#define ABC_PUBLISHER_AGENT_HPP

#include "i_agent.hpp"
#include "event.hpp"
#include "i_enqueuer.hpp"
#include "common.hpp"
#include "thread.hpp"

namespace smart_home{

class ABCPublisherAgent : public IAgent {
public:
    virtual ~ABCPublisherAgent();
    void SetEnqueuer(IEnqueuer* a_enqueuer);

    virtual void Init(const Id& a_id, const Type& a_type, const Floor& a_floor, const Room& a_room
            , const Log& a_log = "", const Config& a_config = "") = 0;
    void Publish(const Event& a_event);
    void Start();
    virtual void Work() = 0;

private:
    IEnqueuer* m_enqueuer;
    std::tr1::shared_ptr<experis::Thread> m_thread;
};

inline ABCPublisherAgent::~ABCPublisherAgent()
{
    m_thread->Join();
}

inline void ABCPublisherAgent::SetEnqueuer(IEnqueuer* a_enqueuer)
{
    m_enqueuer = a_enqueuer;
}

inline void ABCPublisherAgent::Publish(const Event& a_event)
{
    m_enqueuer->Enqueue(a_event);
}

inline void ABCPublisherAgent::Start() 
{
    std::tr1::shared_ptr<advcpp::Runnable> workPtr(new advcpp::RunabbleTemplateMemFunc<ABCPublisherAgent>(*this, &ABCPublisherAgent::Work));
    m_thread = std::tr1::shared_ptr<experis::Thread>(new experis::Thread(workPtr));
}

} //smart_home

#endif //ABC_PUBLISHER_AGENT_HPP