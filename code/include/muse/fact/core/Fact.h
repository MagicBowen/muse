#ifndef H2D3E328D_0E7D_462E_B42D_5F8054156486
#define H2D3E328D_0E7D_462E_B42D_5F8054156486

#include <muse/base/keywords.h>

MUSE_NS_BEGIN

struct Event;

DEF_INTERFACE(Fact)
{
    ABSTRACT(bool confirm(const Event&));
};

MUSE_NS_END

#endif
