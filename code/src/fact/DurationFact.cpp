#include <muse/fact/DurationFact.h>

MUSE_NS_BEGIN

DurationFact::DurationFact(unsigned int maxSeconds)
: maxSeconds(maxSeconds)
{
}

bool DurationFact::doComfirm(const Event& event)
{
    return (++currentSeconds >= maxSeconds);
}

MUSE_NS_END
