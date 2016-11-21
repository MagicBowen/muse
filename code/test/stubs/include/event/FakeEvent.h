#ifndef H66D09416_AA70_4D87_99DD_F10BCCECD3F7
#define H66D09416_AA70_4D87_99DD_F10BCCECD3F7

#include <muse/event/Event.h>

MUSE_NS_BEGIN

enum FakeEventType
{
    NOTHING,
    COLLISION,
    DISTANCE,
    SPEED
};

struct FakeEvent : Event
{
    explicit FakeEvent(FakeEventType type, double value = 0)
    : type(type), value(value)
    {
    }

    OVERRIDE(std::string detail() const);

    FakeEventType type;
    double value;
};

MUSE_NS_END

#define E_NOTHING()         FakeEvent(NOTHING)
#define E_COLLISION()       FakeEvent(COLLISION)
#define E_DISTANCE(VALUE)   FakeEvent(DISTANCE, VALUE)
#define E_SPEED(VALUE)      FakeEvent(SPEED, VALUE)

#endif
