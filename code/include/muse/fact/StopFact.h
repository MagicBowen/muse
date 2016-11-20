#ifndef HDF4A852D_0DF7_4BA7_BEB4_42CCA922EC88
#define HDF4A852D_0DF7_4BA7_BEB4_42CCA922EC88

#include <muse/fact/core/BaseFact.h>

MUSE_NS_BEGIN

DEF_FACT(StopFact)
{
private:
    OVERRIDE(bool doComfirm(const Event&));
};


MUSE_NS_END

#endif
