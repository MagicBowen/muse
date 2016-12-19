#ifndef H3BD6C634_7851_45DF_A9F3_3B72FEA35C86
#define H3BD6C634_7851_45DF_A9F3_3B72FEA35C86

#include <muse/promise/ParallelPromise.h>

MUSE_NS_BEGIN

struct ConcurrentPromise : ParallelPromise
{
private:
    OVERRIDE(bool isFailed() const);
    OVERRIDE(bool isSuccess() const);
};

MUSE_NS_END

#endif
