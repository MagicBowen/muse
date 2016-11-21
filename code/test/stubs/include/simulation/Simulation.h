#ifndef H293F1C24_CEDB_4418_A9CE_16EF2A80FFCF
#define H293F1C24_CEDB_4418_A9CE_16EF2A80FFCF

#include <muse/muse.h>

MUSE_NS_BEGIN

struct EventFetcher;
struct Promise;
struct Event;

struct Simulation
{
    Simulation(EventFetcher&);
    void setPromise(Promise&);
    void setDuration(unsigned int seconds);
    void play();
    void stop();
    bool isSuccess() const;

private:
    void updateTime();
    bool isTimeOut() const;
    void proceed();
    void terminate();
    bool processEvent(const Event&);

private:
    unsigned int durationSeconds{10};
    unsigned int elaspedSeconds{0};
    EventFetcher& fetcher;
    Promise * promise{nullptr};
    bool result{false};
};

MUSE_NS_END

#endif
