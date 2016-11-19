#include <muse/fact/core/OrFact.h>

MUSE_NS_BEGIN

OrFact::OrFact(std::initializer_list<BaseFact*> facts)
: facts(facts)
{
}

bool OrFact::doComfirm(const Event& event)
{
    for(auto fact : facts)
    {
        if(fact->confirm(event)) return true;
    }

    return false;
}

MUSE_NS_END
