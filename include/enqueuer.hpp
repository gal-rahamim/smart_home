#ifndef ENQUEUER_HPP
#define ENQUEUER_HPP

#include "i_enqueuer.hpp"
#include "unbounded_waitable_queue.hpp"

namespace smart_home {

class Enqueuer : public IEnqueuer {
public:
    Enqueuer(advcpp::UnboundedWaitableQueue<Event>& a_queue);

    virtual void Enqueue(const Event& a_event);

private:
    advcpp::UnboundedWaitableQueue<Event>& m_queue;

};

inline Enqueuer::Enqueuer(advcpp::UnboundedWaitableQueue<Event>& a_queue)
: m_queue(a_queue)
{}

inline void Enqueuer::Enqueue(const Event& a_event)
{
    m_queue.Enqueue(a_event);
}

} //smart_home

#endif //ENQUEUER_HPP