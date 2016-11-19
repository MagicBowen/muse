#include <muse/fact/core/BaseFact.h>

MUSE_NS_BEGIN

bool BaseFact::confirm(const Event& event)
{
    if(occurred) return true;

    return doComfirm(event);
}

MUSE_NS_END
