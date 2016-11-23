#include <stubs/include/fact/Duration.h>

MUSE_NS_BEGIN

Duration::Duration(Pred<unsigned int> pred)
: pred(pred)
{
}

bool Duration::handleEvent(const FakeEvent& event)
{
    return pred(++currentSeconds);
}

MUSE_NS_END
