#include <muse/fact/core/AnyOfFact.h>
#include <algorithm>

MUSE_NS_BEGIN

AnyOfFact::AnyOfFact(std::initializer_list<Fact*> facts)
: facts(facts)
{
}

bool AnyOfFact::doComfirm(const Event& event)
{
    return std::any_of(std::begin(facts), std::end(facts), [&event](Fact* fact){return fact->confirm(event);});
}

MUSE_NS_END
