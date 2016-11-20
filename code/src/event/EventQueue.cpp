#include <muse/event/EventQueue.h>
#include <muse/event/Event.h>
#include <list>

MUSE_NS_BEGIN

namespace
{
    std::list<const Event*> events;
}

const Event* EventQueue::fetch()
{
    if(events.empty()) return nullptr;

    const auto& event = events.front();
    events.pop_front();

    return event;
}

void EventQueue::push(const Event& event)
{
    events.push_back(&event);
}

void EventQueue::clear()
{
    events.clear();
}

MUSE_NS_END