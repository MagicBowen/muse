#ifndef H4DD24570_976D_46C4_A912_6724441EBB8B
#define H4DD24570_976D_46C4_A912_6724441EBB8B

#include <muse/promise/CompositePromise.h>

MUSE_NS_BEGIN

struct ParallelPromise : CompositePromise
{
private:
    OVERRIDE(void start());
    OVERRIDE(void stop());
    OVERRIDE(void handle(const Event&));
    OVERRIDE(Result evaluate() const);

private:
    void updateResult();

private:
    ABSTRACT(bool isFailed() const);
    ABSTRACT(bool isSuccess() const);

private:
    Result result;
};

MUSE_NS_END

#endif
