#include <muse/fact/AllFact.h>
#include <muse/base/Algorithm.h>

MUSE_NS_BEGIN

AllOfFact::AllOfFact(std::initializer_list<Fact*> facts)
: facts(facts)
{
}

bool AllOfFact::doComfirm(const Event& event)
{
    return allof(facts, [&event](Fact* f){return f->confirm(event);});
}

MUSE_NS_END
