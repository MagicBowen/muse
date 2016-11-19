#include <muse/fact/core/OrFact.h>

MUSE_NS_BEGIN

OrFact::OrFact(std::initializer_list<Fact*> facts)
: facts(facts)
{
}

bool OrFact::doSatisfyWith(const Event& event)
{
    for(auto fact : facts)
    {
        if(fact->satisfyWith(event)) return true;
    }

    return false;
}

MUSE_NS_END
