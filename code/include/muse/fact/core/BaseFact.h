#ifndef HA5D3A510_8DBE_4634_B217_17E75FB75DFA
#define HA5D3A510_8DBE_4634_B217_17E75FB75DFA

#include <muse/fact/core/Fact.h>
#include <string>

MUSE_NS_BEGIN

struct BaseFact : Fact
{
private:
    OVERRIDE(bool confirm(const Event&));
    OVERRIDE(void dump() const);

private:
    ABSTRACT(bool doComfirm(const Event&));
    ABSTRACT(const char* name() const);
    DEFAULT(std::string, info() const);

private:
    bool occurred{false};
};

MUSE_NS_END

//////////////////////////////////////////////////////
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
