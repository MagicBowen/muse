#include <muse/fact/ClosureFact.h>

MUSE_NS_BEGIN

ClosureFact::ClosureFact(Fact& fact)
: fact(fact)
{
}

bool ClosureFact::isOccurred() const
{
    return occurred;
}

void ClosureFact::start()
{
    fact.start();
}

void ClosureFact::stop()
{
    fact.stop();
    occurred = fact.isOccurred();
}

void ClosureFact::confirm(const Event& event)
{
    fact.confirm(event);
}

std::string ClosureFact::info() const
{
    return fact.info();
}

MUSE_NS_END
