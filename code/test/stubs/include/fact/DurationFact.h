#ifndef H106C811B_25AE_4E37_8338_3299DADF6841
#define H106C811B_25AE_4E37_8338_3299DADF6841

#include <stubs/include/fact/FakeFact.h>

MUSE_NS_BEGIN

DEF_FACT_BASE_OF(DurationFact, FakeFact)
{
    explicit DurationFact(unsigned int maxSeconds);

private:
    OVERRIDE(bool handleEvent(const FakeEvent&));

private:
    unsigned int maxSeconds;
    unsigned int currentSeconds{0};
};

MUSE_NS_END

#endif
