#ifndef I_AGENT_LOADER_HPP
#define I_AGENT_LOADER_HPP

#include <vector>
#include "i_agent.hpp"

namespace smart_home {

class IAgentLoader {
public:
    typedef std::vector<std::tr1::shared_ptr<IAgent> > AgentPtrCont;

public:
    virtual ~IAgentLoader();
    virtual void Load(AgentPtrCont& a_resAgentCont) = 0;
};

inline IAgentLoader::~IAgentLoader(){}

} //smart_home

#endif //I_AGENT_LOADER_HPP