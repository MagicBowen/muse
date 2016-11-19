#ifndef HA5D3A510_8DBE_4634_B217_17E75FB75DFA
#define HA5D3A510_8DBE_4634_B217_17E75FB75DFA

#include <muse/base/keywords.h>

MUSE_NS_BEGIN

struct Event;

DEF_INTERFACE(Fact)
{
    bool satisfyWith(const Event&);

private:
    ABSTRACT(bool doSatisfyWith(const Event&));

private:
    bool satisfied{false};
};

MUSE_NS_END

#endif
