#ifndef HA5D3A510_8DBE_4634_B217_17E75FB75DFA
#define HA5D3A510_8DBE_4634_B217_17E75FB75DFA

#include <muse/fact/core/Fact.h>

MUSE_NS_BEGIN

struct BaseFact : Fact
{
    OVERRIDE(bool confirm(const Event&));

private:
    ABSTRACT(bool doComfirm(const Event&));

private:
    bool occurred{false};
};

MUSE_NS_END

#define BASE_FACT(FACT)  FACT##Base

#define DEF_FACT(FACT)                      \
struct BASE_FACT(FACT) : BaseFact           \
{                                           \
private:                                    \
    OVERRIDE(const char* name() const)      \
    {                                       \
        return #FACT;                       \
    }                                       \
};                                          \
struct FACT : BASE_FACT(FACT)

#endif
