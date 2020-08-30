#include <sstream>
#include "so_lib_pattern.hpp"

namespace advcpp {

std::string SoLibPattern::GetLibName(const std::string& a_identifier)
{
    std::ostringstream s;
    s << "./lib" << a_identifier << ".so";
    return s.str();
}


} //advcpp