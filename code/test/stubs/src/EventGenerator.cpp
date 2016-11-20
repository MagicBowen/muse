#include <stubs/include/EventGenerator.h>
#include <muse/event/EventQueue.h>

MUSE_NS_BEGIN

void EventGenerator::generate(EventType type, double value)
{
    auto event = createEvent(type, value);
    EventQueue::getInstance().push(*event);
}

Event* EventGenerator::createEvent(EventType type, double value)
{
    auto event = std::make_shared<Event>(type, value);
    events.push_back(event);
    return event.get();
}

EventGenerator::~EventGenerator()
{
    EventQueue::getInstance().clear();
}

MUSE_NS_END
