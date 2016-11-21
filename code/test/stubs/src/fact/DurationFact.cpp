#include <stubs/include/fact/DurationFact.h>

MUSE_NS_BEGIN

DurationFact::DurationFact(unsigned int maxSeconds)
: maxSeconds(maxSeconds)
{
}

bool DurationFact::handleEvent(const FakeEvent& event)
{
    return (++currentSeconds >= maxSeconds);
}

MUSE_NS_END
