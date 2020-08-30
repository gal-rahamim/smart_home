#ifndef SUBSCIPTION_LOCATOR_HPP
#define SUBSCIPTION_LOCATOR_HPP

#include "i_subscription_locator.hpp"
#include "subscription_table.hpp"

namespace smart_home {

class SubscriptionLocator : public ISubscriptionLocator {
public:
    SubscriptionLocator(SubsriptionTable& a_table);
    virtual void FindAgents(const Event& a_event, HandlingAgents& a_resAgents);

private: 
    SubsriptionTable& m_table;  
};

inline SubscriptionLocator::SubscriptionLocator(SubsriptionTable& a_table)
: m_table(a_table)
{}

inline void SubscriptionLocator::FindAgents(const Event& a_event
                                , HandlingAgents& a_resAgents)
{
    m_table.Find(a_event.GetType(), a_event.GetFloor(), a_event.GetRoom(), a_resAgents);
}

} //smart_home

#endif //SUBSCIPTION_LOCATOR_HPP