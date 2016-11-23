#ifndef H971956FB_1B6D_4471_95FC_6496A64A24E4
#define H971956FB_1B6D_4471_95FC_6496A64A24E4

#include <stubs/include/fact/FakeFact.h>
#include <stubs/include/pred/Pred.h>

MUSE_NS_BEGIN

DEF_FACT_BASE_OF(Distance, FakeFact)
{
    explicit Distance(Pred<double> pred);

private:
    OVERRIDE(bool handleEvent(const FakeEvent&));

private:
    Pred<double> pred;
};


MUSE_NS_END

#endif
