#ifndef H44C3EA49_4087_4A41_B3F8_3FFD796941F3
#define H44C3EA49_4087_4A41_B3F8_3FFD796941F3

#include <muse/fact/FactHelper.h>

MUSE_NS_BEGIN

struct FakeEvent;

DEF_FACT(FakeFact)
{
private:
    OVERRIDE(bool doComfirm(const Event&));

private:
    ABSTRACT(bool handleEvent(const FakeEvent&));
};

MUSE_NS_END

#endif
