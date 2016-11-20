#include <muse/fact/core/AnyFact.h>
#include <muse/base/Algorithm.h>

MUSE_NS_BEGIN

AnyOfFact::AnyOfFact(std::initializer_list<Fact*> facts)
: facts(facts)
{
}

bool AnyOfFact::doComfirm(const Event& event)
{
    return anyof(facts, [&event](Fact* f){return f->confirm(event);});
}

MUSE_NS_END
