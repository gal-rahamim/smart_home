#ifndef I_DYNAMIC_LIB_HPP
#define I_DYNAMIC_LIB_HPP

#include <string>
#include <map>
#include <dlfcn.h>

namespace advcpp {

class IDynamicLib {
public:
    virtual ~IDynamicLib() {}

    virtual void GetFunction(const std::string& a_funcName) = 0;
};

} //advcpp

#endif //I_DYNAMIC_LIB_HPP