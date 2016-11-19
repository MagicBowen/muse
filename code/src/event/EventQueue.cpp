#include <muse/event/EventQueue.h>
#include <muse/event/Event.h>
#include <list>

MUSE_NS_BEGIN

namespace
{
    std::list<Event> events;
}

const Event* EventQueue::fetch()
{
    if(events.empty()) return nullptr;

    const auto& event = events.front();
    events.pop_front();

    return &event;
}

void EventQueue::push(const Event& event)
{
    events.push_back(event);
}

MUSE_NS_END
