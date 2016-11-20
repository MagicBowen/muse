#ifndef H8904FFC6_6830_4955_B7E2_4C7FB41237C8
#define H8904FFC6_6830_4955_B7E2_4C7FB41237C8

#include <muse/muse.h>

MUSE_NS_BEGIN

enum EventType
{
    NOTHING,
    COLLISION,
    DISTANCE,
    SPEED
};

struct Event
{
    Event(EventType type, double value = 0)
    : type(type), value(value)
    {
    }

    EventType type;
    double value;
};

MUSE_NS_END

#endif
