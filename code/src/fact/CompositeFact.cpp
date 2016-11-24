#include <muse/fact/CompositeFact.h>
#include <muse/base/StdExt.h>

MUSE_NS_BEGIN

void CompositeFact::clear()
{
    facts.clear();
}

void CompositeFact::addFact(Fact& fact)
{
    facts.push_back(&fact);
}

void CompositeFact::onStarted()
{
    foreach(facts, [](Fact* f){ f->onStarted(); });
}

void CompositeFact::onStopped()
{
    foreach(facts, [](Fact* f){ f->onStopped(); });
}

MUSE_NS_END
