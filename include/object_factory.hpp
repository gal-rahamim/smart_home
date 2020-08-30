#ifndef OBJECT_FACTORY_HPP
#define OBJECT_FACTORY_HPP

#include <tr1/memory>
#include "so_lib.hpp"
#include "common.hpp"
#include "so_lib_pattern.hpp"

namespace advcpp {

template<class T>
class ObjectFactory : private UnCopyable {
public:
    ObjectFactory();

    //rules:
    //lib name must be "lib" + identifier + ".so"
    //lib must be in the same folder as main
    //lib must have an extern "C" function called "CreateObject"
    
    T GetObject(const std::string& a_identifier);

private:
    typedef T (*ObjectCreator)(void);
    typedef std::tr1::shared_ptr<SoLib> SoLibPtr;
    typedef std::map<std::string, SoLibPtr> Libraries;
    typedef Libraries::const_iterator citer;

private:
    Libraries m_soLibs;
    SoLibPattern m_libNameModifier;
};

} //advcpp

#include "inl/object_factory.hxx"

#endif //OBJECT_FACTORY_HPP