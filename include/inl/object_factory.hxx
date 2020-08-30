#ifndef OBJECT_FACTORY_HXX
#define OBJECT_FACTORY_HXX

#include "object_factory.hpp"

namespace advcpp {

template<class T>
ObjectFactory<T>::ObjectFactory()
: m_soLibs()
, m_libNameModifier()
{}

template<class T>
T ObjectFactory<T>::GetObject(const std::string& a_identifier)
{
    std::string libName = m_libNameModifier.GetLibName(a_identifier);
    citer it = m_soLibs.find(libName);
    ObjectCreator oc;
    if(it == m_soLibs.end()) {
        SoLibPtr newLib(new SoLib(libName));
        oc = newLib->GetFunction<ObjectCreator>("CreateObject");
        m_soLibs.insert(std::make_pair<std::string, SoLibPtr>(libName, newLib));
    }
    else {
        oc = it->second->GetFunction<ObjectCreator>("CreateObject");
    }
    T ret = oc();
    return ret;
}

} //advcpp

#endif //OBJECT_FACTORY_HXX