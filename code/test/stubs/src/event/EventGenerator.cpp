#include <stubs/include/event/EventGenerator.h>
#include <muse/base/Algorithm.h>

MUSE_NS_BEGIN

void EventGenerator::generate(std::initializer_list<FakeEvent> fakeEvents)
{
    foreach(fakeEvents, [this](const FakeEvent& event) {events.push_back(event);});
    current = events.begin();

}

const Event* EventGenerator::fetch()
{
    if(current == events.end()) return nullptr;
    return &(*(current++));
}

MUSE_NS_END
