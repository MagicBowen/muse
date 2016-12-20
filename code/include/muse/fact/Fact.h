#ifndef H2D3E328D_0E7D_462E_B42D_5F8054156486
#define H2D3E328D_0E7D_462E_B42D_5F8054156486

#include <muse/base/keywords.h>
#include <string>

MUSE_NS_BEGIN

struct Event;

DEF_INTERFACE(Fact)
{
    DEFAULT(void, start());
    DEFAULT(void, stop());
    ABSTRACT(void confirm(const Event&));
    ABSTRACT(bool isOccurred() const);
    DEFAULT(std::string, info() const);
};

MUSE_NS_END

#endif
