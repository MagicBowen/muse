#ifndef HE03F10BF_A2A7_491D_BE87_F335E6FCCA40
#define HE03F10BF_A2A7_491D_BE87_F335E6FCCA40

#include <muse/base/keywords.h>
#include <string>

MUSE_NS_BEGIN

template<typename T>
struct Pred
{
    ABSTRACT(bool operator()(const T& value) const);
    ABSTRACT(std::string info() const);
    virtual ~Pred<T>(){}
};

MUSE_NS_END

#endif
