#ifndef I_SUBSCIPTION_LOCATOR_HPP
#define I_SUBSCIPTION_LOCATOR_HPP

#include <vector>
#include <tr1/memory>
#include "event.hpp"
#include "abc_subscriber_agent.hpp"

namespace smart_home {

class ISubscriptionLocator {
public: 
    typedef std::vector<std::tr1::shared_ptr<ABCSubscriberAgent> > HandlingAgents;

public:
    virtual ~ISubscriptionLocator();
    virtual void FindAgents(const Event& a_event, HandlingAgents& a_resAgents) = 0;

};

inline ISubscriptionLocator::~ISubscriptionLocator(){}

} //smart_home

#endif //I_SUBSCIPTION_LOCATOR_HPP