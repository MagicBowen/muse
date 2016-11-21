#ifndef HA5D3A510_8DBE_4634_B217_17E75FB75DFA
#define HA5D3A510_8DBE_4634_B217_17E75FB75DFA

#include <muse/fact/Fact.h>
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

#endif
