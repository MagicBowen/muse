#ifndef H5C8DB16B_D346_4441_855D_F644BAC74FAF
#define H5C8DB16B_D346_4441_855D_F644BAC74FAF

#include <muse/promise/Promise.h>

MUSE_NS_BEGIN

struct DecoratorPromise : Promise
{
    DecoratorPromise(Promise& decorator, Promise& promise);

private:
    OVERRIDE(void start());
    OVERRIDE(void stop());
    OVERRIDE(void handle(const Event&));
    OVERRIDE(Result evaluate() const);

private:
    void terminate();

private:
    ABSTRACT(bool isFinished() const);
    ABSTRACT(void fixResult());

protected:
    Promise& decorator;
    Promise& promise;
    Result result;
};

MUSE_NS_END

#endif
