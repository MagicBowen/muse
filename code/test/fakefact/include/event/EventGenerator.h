#ifndef H263BECEA_1079_475A_A842_56D739E5252D
#define H263BECEA_1079_475A_A842_56D739E5252D

#include <fakefact/include/event/FakeEvent.h>
#include <fakefact/include/event/EventFetcher.h>
#include <initializer_list>
#include <list>

MUSE_NS_BEGIN

struct EventGenerator : EventFetcher
{
    void generate(std::initializer_list<FakeEvent>);

private:
    OVERRIDE(const Event* fetch());

private:
    using Events = std::list<FakeEvent>;
    Events events;
    Events::iterator current;

};

MUSE_NS_END

#endif
