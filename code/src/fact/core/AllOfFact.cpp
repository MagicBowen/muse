#include <muse/fact/core/AllOfFact.h>
#include <algorithm>

MUSE_NS_BEGIN

AllOfFact::AllOfFact(std::initializer_list<Fact*> facts)
: facts(facts)
{
}

bool AllOfFact::doComfirm(const Event& event)
{
    return std::all_of(std::begin(facts), std::end(facts), [&event](Fact* fact){return fact->confirm(event);});
}

MUSE_NS_END
