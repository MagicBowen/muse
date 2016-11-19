#ifndef H27E0CA63_7BAB_42D9_B7A0_B6DE1F309B25
#define H27E0CA63_7BAB_42D9_B7A0_B6DE1F309B25

#include <muse/fact/core/Fact.h>

MUSE_NS_BEGIN

struct CollisionFact : Fact
{
private:
    OVERRIDE(bool doSatisfyWith(const Event&));
};

MUSE_NS_END

#endif
