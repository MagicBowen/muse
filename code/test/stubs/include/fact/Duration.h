#ifndef H106C811B_25AE_4E37_8338_3299DADF6841
#define H106C811B_25AE_4E37_8338_3299DADF6841

#include <stubs/include/fact/FakeFact.h>
#include <stubs/include/pred/Pred.h>

MUSE_NS_BEGIN

DEF_FACT_BASE_OF(Duration, FakeFact)
{
    explicit Duration(Pred<unsigned int> pred);

private:
    OVERRIDE(bool handleEvent(const FakeEvent&));

private:
    unsigned int currentSeconds{0};
    Pred<unsigned int> pred;
};

MUSE_NS_END

#endif
