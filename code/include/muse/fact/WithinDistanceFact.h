#ifndef H971956FB_1B6D_4471_95FC_6496A64A24E4
#define H971956FB_1B6D_4471_95FC_6496A64A24E4

#include <muse/fact/fact.h>

MUSE_NS_BEGIN

struct WithinDistanceFact : Fact
{
    WithinDistanceFact(double range);

private:
    OVERRIDE(bool occurred(const Event&));

private:
    double range;
};


MUSE_NS_END

#endif
