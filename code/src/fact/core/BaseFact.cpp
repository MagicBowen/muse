#include <muse/fact/core/BaseFact.h>

MUSE_NS_BEGIN

bool BaseFact::confirm(const Event& event)
{
    if(occurred) return true;

    occurred = doComfirm(event);
    return occurred;
}

MUSE_NS_END
