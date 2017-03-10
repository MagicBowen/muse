#ifndef H971956FB_1B6D_4471_95FC_6496A64A24E4
#define H971956FB_1B6D_4471_95FC_6496A64A24E4

#include <muse/fact/FactHelper.h>
#include <fakefact/include/fact/FakeFact.h>

MUSE_NS_BEGIN

DEF_PRED_FACT_BASE_OF(Distance, FakeFact, double)
{
private:
    OVERRIDE(bool handleEvent(const FakeEvent&));
    OVERRIDE(std::string detail() const);
};


MUSE_NS_END

#endif
