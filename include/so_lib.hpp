#ifndef SO_LIB_HPP
#define SO_LIB_HPP

#include <string>
#include <map>
#include <dlfcn.h>
#include "common.hpp"

namespace advcpp {

class SoLib : private UnCopyable {
public:
    SoLib(const std::string& a_libName, int a_flag = RTLD_NOW);
    ~SoLib();

    template<typename PF>
    PF GetFunction(const std::string& a_funcName);

private:
    typedef std::map<std::string, void*>::iterator iter;
    typedef std::map<std::string, void*>::const_iterator citer;

private:
    void* m_handler;
    std::map<std::string, void*> m_funcContainer;
};

} //advcpp

#include "inl/so_lib.hxx"

#endif //SO_LIB_HPP