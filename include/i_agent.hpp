#ifndef I_AGENT_HPP
#define I_AGENT_HPP

#include <string>

namespace smart_home {

class IAgent {
public:
    typedef std::string Id;
    typedef std::string Type;
    typedef std::string Floor;
    typedef std::string Room;
    typedef std::string Log;
    typedef std::string Config;
    
public:
    virtual ~IAgent();

    virtual void Init(const Id& a_id, const Type& a_type, const Floor& a_floor, const Room& a_room
            , const Log& a_log = "", const Config& a_config = "") = 0;
    virtual void Work() = 0;
};

inline IAgent::~IAgent(){}

} //smart_home

#endif //I_AGENT_HPP