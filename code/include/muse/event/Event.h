#ifndef H8904FFC6_6830_4955_B7E2_4C7FB41237C8
#define H8904FFC6_6830_4955_B7E2_4C7FB41237C8

#include <muse/base/keywords.h>
#include <string>

MUSE_NS_BEGIN

DEF_INTERFACE(Event)
{
    ABSTRACT(std::string info() const);
};

MUSE_NS_END

#endif
