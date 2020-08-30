#ifndef SO_LIB_HXX
#define SO_LIB_HXX

#include <exception>
#include <stdexcept>
#include "so_lib.hpp"

namespace advcpp{

template<typename PF>
PF SoLib::GetFunction(const std::string& a_funcName)
{
    PF PFunc;
    citer it = m_funcContainer.find(a_funcName);
    if(m_funcContainer.end() == it) {
        void* rawPF = ::dlsym(m_handler, a_funcName.c_str());
        PFunc = reinterpret_cast<PF>(rawPF);
        if(!PFunc) {
            throw std::runtime_error(::dlerror());
        }
        m_funcContainer.insert(std::make_pair<std::string, void*>(a_funcName,rawPF));
    }
    else {
        PFunc = reinterpret_cast<PF>(it->second);
    }
    return PFunc;
}
} //advcpp

#endif //SO_LIB_HXX