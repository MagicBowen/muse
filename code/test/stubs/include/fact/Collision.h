#ifndef H27E0CA63_7BAB_42D9_B7A0_B6DE1F309B25
#define H27E0CA63_7BAB_42D9_B7A0_B6DE1F309B25

#include <stubs/include/fact/FakeFact.h>

MUSE_NS_BEGIN

DEF_FACT_BASE_OF(Collision, FakeFact)
{
private:
    OVERRIDE(bool handleEvent(const FakeEvent&));
};

MUSE_NS_END

#endif
