#ifndef H0F29B976_6657_4E6D_B2E2_8786ED982CD3
#define H0F29B976_6657_4E6D_B2E2_8786ED982CD3

#include <muse/base/keywords.h>

MUSE_NS_BEGIN

struct Event;

DEF_INTERFACE(EventFetcher)
{
    ABSTRACT(const Event* fetch());
};

MUSE_NS_END

#endif
