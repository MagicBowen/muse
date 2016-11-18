#ifndef H8904FFC6_6830_4955_B7E2_4C7FB41237C8
#define H8904FFC6_6830_4955_B7E2_4C7FB41237C8

#include <muse/muse.h>

MUSE_NS_BEGIN

enum EventType
{
    COLLISION,
    DISTANCE,
    SPEED,
    NOTHING
};

struct Event
{
    EventType type;
    double value;
};

MUSE_NS_END

#endif
