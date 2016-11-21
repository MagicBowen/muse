#ifndef H4DD24570_976D_46C4_A912_6724441EBB8B
#define H4DD24570_976D_46C4_A912_6724441EBB8B

#include <muse/promise/Promise.h>
#include <initializer_list>
#include <list>

MUSE_NS_BEGIN

struct ParallelPromise : Promise
{
    explicit ParallelPromise(std::initializer_list<Promise*>);

private:
    OVERRIDE(void start());
    OVERRIDE(void stop());
    OVERRIDE(void onEvent(const Event&));
    OVERRIDE(Result evaluate() const);

private:
    void updateResult();

private:
    ABSTRACT(bool isFailed() const);
    ABSTRACT(bool isSuccess() const);

protected:
    using Promises = std::list<Promise*>;
    std::list<Promise*> promises;
    Result result{Result::UNKNOWN};
};

MUSE_NS_END

#endif
