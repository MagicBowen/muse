#include <muse/fact/core/Fact.h>

MUSE_NS_BEGIN

bool Fact::satisfyWith(const Event& event)
{
    if(satisfied) return true;

    return doSatisfyWith(event);
}

MUSE_NS_END
