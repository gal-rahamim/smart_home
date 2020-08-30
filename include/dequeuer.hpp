#ifndef DEQUEUER_HPP
#define DEQUEUER_HPP

#include "i_dequeuer.hpp"
#include "unbounded_waitable_queue.hpp"

namespace smart_home {

class Dequeuer : public IDequeuer {
public:
    Dequeuer(advcpp::UnboundedWaitableQueue<Event>& a_queue);

    virtual void Dequeue(Event& a_event);

private:
    advcpp::UnboundedWaitableQueue<Event>& m_queue;

};

inline Dequeuer::Dequeuer(advcpp::UnboundedWaitableQueue<Event>& a_queue)
: m_queue(a_queue)
{}

inline void Dequeuer::Dequeue(Event& a_event)
{
    m_queue.Dequeue(a_event);
}

} //smart_home

#endif //DEQUEUER_HPP