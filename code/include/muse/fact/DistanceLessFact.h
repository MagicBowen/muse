#ifndef H971956FB_1B6D_4471_95FC_6496A64A24E4
#define H971956FB_1B6D_4471_95FC_6496A64A24E4

#include <muse/fact/core/BaseFact.h>

MUSE_NS_BEGIN

DEF_FACT(DistanceLessFact)
{
    DistanceLessFact(double range);

private:
    OVERRIDE(bool doComfirm(const Event&));

private:
    double range;
};


MUSE_NS_END

#endif
