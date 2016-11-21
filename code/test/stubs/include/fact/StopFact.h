#ifndef HDF4A852D_0DF7_4BA7_BEB4_42CCA922EC88
#define HDF4A852D_0DF7_4BA7_BEB4_42CCA922EC88

#include <stubs/include/fact/FakeFact.h>

MUSE_NS_BEGIN

DEF_FACT_BASE_OF(StopFact, FakeFact)
{
private:
    OVERRIDE(bool handleEvent(const FakeEvent&));
};


MUSE_NS_END

#endif
