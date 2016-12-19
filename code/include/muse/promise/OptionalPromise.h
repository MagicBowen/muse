#ifndef H6E130008_291C_4D5A_AC0D_66B8AE81AD82
#define H6E130008_291C_4D5A_AC0D_66B8AE81AD82

#include <muse/promise/ParallelPromise.h>

MUSE_NS_BEGIN

struct OptionalPromise : ParallelPromise
{
private:
    OVERRIDE(bool isFailed() const);
    OVERRIDE(bool isSuccess() const);
};

MUSE_NS_END

#endif
