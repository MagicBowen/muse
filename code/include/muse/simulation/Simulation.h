#ifndef H293F1C24_CEDB_4418_A9CE_16EF2A80FFCF
#define H293F1C24_CEDB_4418_A9CE_16EF2A80FFCF

#include <muse/muse.h>

MUSE_NS_BEGIN

struct Validator;
struct Event;

struct Simulation
{
    Simulation(Validator&);
    void play();
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
    Validator& validator;
    bool result{false};
};

MUSE_NS_END

#endif
