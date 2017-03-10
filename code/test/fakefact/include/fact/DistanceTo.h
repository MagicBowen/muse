#ifndef HFE8EC75C_F97A_46E8_8F5B_AA60558F0E08
#define HFE8EC75C_F97A_46E8_8F5B_AA60558F0E08

#include <muse/fact/FactHelper.h>
#include <fakefact/include/fact/FakeFact.h>

MUSE_NS_BEGIN

DEF_PRED_FACT_BASE_OF(DistanceTo, FakeFact, double)
{
    DistanceTo(int id);
private:
    OVERRIDE(bool handleEvent(const FakeEvent&));
    OVERRIDE(std::string detail() const);

private:
    int id{0};
};


MUSE_NS_END

#endif
