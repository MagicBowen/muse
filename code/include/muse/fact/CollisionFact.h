#ifndef H27E0CA63_7BAB_42D9_B7A0_B6DE1F309B25
#define H27E0CA63_7BAB_42D9_B7A0_B6DE1F309B25

#include <muse/fact/core/BaseFact.h>

MUSE_NS_BEGIN

DEF_FACT(CollisionFact)
{
private:
    OVERRIDE(bool doComfirm(const Event&));
};

MUSE_NS_END

#endif
