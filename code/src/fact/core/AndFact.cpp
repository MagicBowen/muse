#include <muse/fact/core/AndFact.h>

MUSE_NS_BEGIN

AndFact::AndFact(std::initializer_list<Fact*> facts)
: facts(facts)
{
}

bool AndFact::doSatisfyWith(const Event& event)
{
    for(auto fact : facts)
    {
        if(!fact->satisfyWith(event)) return false;
    }

    return true;
}

MUSE_NS_END
