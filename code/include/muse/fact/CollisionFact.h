#ifndef H27E0CA63_7BAB_42D9_B7A0_B6DE1F309B25
#define H27E0CA63_7BAB_42D9_B7A0_B6DE1F309B25

#include "Fact.h"

MUSE_NS_BEGIN

struct CollisionFact : Fact
{
private:
    OVERRIDE(bool occurred(const Event&));
};

MUSE_NS_END

#endif
