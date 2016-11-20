#ifndef H106C811B_25AE_4E37_8338_3299DADF6841
#define H106C811B_25AE_4E37_8338_3299DADF6841

#include <muse/fact/core/BaseFact.h>

MUSE_NS_BEGIN

DEF_FACT(DurationFact)
{
    DurationFact(unsigned int maxSeconds);

private:
    OVERRIDE(bool doComfirm(const Event&));

private:
    unsigned int maxSeconds;
    unsigned int currentSeconds{0};
};

MUSE_NS_END

#endif
