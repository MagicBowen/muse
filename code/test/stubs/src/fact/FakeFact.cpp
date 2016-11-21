#include <stubs/include/fact/FakeFact.h>
#include <stubs/include/event/FakeEvent.h>
#include <muse/base/log.h>

using muse::FakeFact;

MUSE_NS_BEGIN

bool FakeFact::doComfirm(const Event& event)
{
    auto fakeEvent = dynamic_cast<const FakeEvent*>(&event);
    if(!fakeEvent)
    {
        ERR_LOG("Fake fact expected fake event!");
        return false;
    }

    return handleEvent(*fakeEvent);
}

MUSE_NS_END
