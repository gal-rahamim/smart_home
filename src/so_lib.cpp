#include <stdexcept> 
#include "so_lib.hpp"

namespace advcpp {

SoLib::SoLib(const std::string& a_libName, int a_flag)
: m_handler(::dlopen(a_libName.c_str(), a_flag))
, m_funcContainer()
{
    if(!m_handler) {
        throw std::runtime_error(::dlerror());
    }
}

SoLib::~SoLib()
{
    dlclose(m_handler);
}

} //advcpp