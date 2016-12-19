#ifndef HC626219A_60D0_4BE2_A8BA_6C8F164C301C
#define HC626219A_60D0_4BE2_A8BA_6C8F164C301C

#include <muse/promise/CompositePromise.h>

MUSE_NS_BEGIN

struct SequentialPromise : CompositePromise
{
private:
    OVERRIDE(void start());
    OVERRIDE(void stop());
    OVERRIDE(void handle(const Event&));
    OVERRIDE(Result evaluate() const);

private:
    void doStop();

    void processEvent(const Event&);
    void onCurrentFailed();
    void onCurrentSuccess();
    bool isFinish() const;
    bool atLast() const;
    bool gotoNext();
    Promise& current();

private:
    OVERRIDE(void reset());

private:
    Promises::iterator currentPromise;
    Result result;
};

MUSE_NS_END

#endif
