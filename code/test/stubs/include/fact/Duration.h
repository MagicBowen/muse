#ifndef H106C811B_25AE_4E37_8338_3299DADF6841
#define H106C811B_25AE_4E37_8338_3299DADF6841

#include <muse/fact/FactHelper.h>
#include <stubs/include/fact/FakeFact.h>

MUSE_NS_BEGIN

DEF_PRED_FACT_BASE_OF(Duration, FakeFact, unsigned int)
{
private:
    OVERRIDE(bool handleEvent(const FakeEvent&));
    OVERRIDE(std::string detail() const);

private:
    unsigned int currentSeconds{0};
};

MUSE_NS_END

#endif
