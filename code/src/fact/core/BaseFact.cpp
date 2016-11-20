#include <muse/fact/core/BaseFact.h>
#include <muse/event/Event.h>
#include <muse/base/log.h>

MUSE_NS_BEGIN

bool BaseFact::confirm(const Event& event)
{
    if(occurred) return true;

    DBG_LOG("%s confirm event(type = %d, value = %d)", name(), event.type, event.value);

    occurred = doComfirm(event);
    if(occurred)
    {
        DBG_LOG("%s confirm occurred!", name());
    }

    return occurred;
}

MUSE_NS_END
