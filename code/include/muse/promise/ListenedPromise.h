#ifndef HAA0821E9_D684_4B33_98FA_9743E0414850
#define HAA0821E9_D684_4B33_98FA_9743E0414850

#include <muse/promise/Promise.h>
#include <list>

MUSE_NS_BEGIN

struct  PromiseListener;

struct ListenedPromise : Promise
{
    ListenedPromise(Promise&);
    void addListener(PromiseListener&);
    void clear();

private:
    OVERRIDE(void start());
    OVERRIDE(void stop());
    OVERRIDE(void handle(const Event&));
    OVERRIDE(Result evaluate() const);

private:
    std::list<PromiseListener*> listeners;
    Promise& promise;
};

MUSE_NS_END

#endif
