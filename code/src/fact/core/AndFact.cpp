#include <muse/fact/core/AndFact.h>

MUSE_NS_BEGIN

AndFact::AndFact(std::initializer_list<BaseFact*> facts)
: facts(facts)
{
}

bool AndFact::doComfirm(const Event& event)
{
    for(auto fact : facts)
    {
        if(!fact->confirm(event)) return false;
    }

    return true;
}

MUSE_NS_END
