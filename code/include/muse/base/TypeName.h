#ifndef H38247538_297F_F680_94D3_8A28246846EF
#define H38247538_297F_F680_94D3_8A28246846EF

#include <muse/muse.h>
#include <string>
#include <typeinfo>

MUSE_NS_BEGIN

///////////////////////////////////////////////////////////////
std::string getDemangledName(const std::type_info& typeInfo);

///////////////////////////////////////////////////////////////
template<typename T>
struct TypeName
{
    static std::string value()
    {
        return typeid(T).name();
    }
};

///////////////////////////////////////////////////////////////
template<>
struct TypeName<std::string>
{
    static std::string value() { return "std::string"; }
};

template<typename T>
const char* nameOf(const T* t)
{
    return typeid(t).name();
}

MUSE_NS_END

#endif
