#include <muse/fact/core/BaseFact.h>
#include <muse/event/Event.h>
#include <muse/base/log.h>
#include <sstream>

MUSE_NS_BEGIN

bool BaseFact::confirm(const Event& event)
{
    if(occurred) return true;

    DBG_LOG("%s confirm event(type = %d, value = %f)", name(), event.type, event.value);

    occurred = doComfirm(event);
    return occurred;
}

void BaseFact::dump() const
{
    static const char* S_OCCURRED[] = {"not occurred", "occurred"};

    std::stringstream ss;
    ss << name() << " is " << S_OCCURRED[occurred] << ".\n";
    ss << "----------------------------------------------------\n";
    ss << (info().empty() ? "No details......" : info())  <<  "\n";
    ss << "----------------------------------------------------";

    WARN_LOG("%s", ss.str().c_str());
}

MUSE_NS_END
