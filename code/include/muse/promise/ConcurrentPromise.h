#ifndef H3BD6C634_7851_45DF_A9F3_3B72FEA35C86
#define H3BD6C634_7851_45DF_A9F3_3B72FEA35C86

#include <muse/promise/Promise.h>
#include <initializer_list>
#include <list>

MUSE_NS_BEGIN

struct ConcurrentPromise : Promise
{
    explicit ConcurrentPromise(std::initializer_list<Promise*>);

private:
    OVERRIDE(void start());
    OVERRIDE(void stop());
    OVERRIDE(void onEvent(const Event&));
    OVERRIDE(Result evaluate() const);

private:
    bool anyFailed() const;
    bool allSuccess() const;
    void updateResult();

private:
    using Promises = std::list<Promise*>;
    std::list<Promise*> promises;
    Result result{Result::UNKNOWN};
};

MUSE_NS_END

#endif
