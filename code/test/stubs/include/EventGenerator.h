#ifndef H263BECEA_1079_475A_A842_56D739E5252D
#define H263BECEA_1079_475A_A842_56D739E5252D

#include <muse/event/Event.h>
#include <vector>
#include <memory>

MUSE_NS_BEGIN

struct EventGenerator
{
    void generate(EventType type, double value);
    ~EventGenerator();

private:
    Event* createEvent(EventType type, double value);

private:
    std::vector<std::shared_ptr<Event>> events;
};

MUSE_NS_END

#endif
