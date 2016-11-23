#ifndef H8191557C_DB50_4576_89D5_6DAD7D234FFB
#define H8191557C_DB50_4576_89D5_6DAD7D234FFB

#include <muse/promise/ExistPromise.h>
#include <muse/promise/NotExistPromise.h>

MUSE_NS_BEGIN

template<typename PROMISE, typename FACT>
struct FactPromiseHelper : PROMISE
{
    FactPromiseHelper(const FACT& f)
    : PROMISE(fact), fact(f)
    {
    }

private:
    FACT fact;
};

MUSE_NS_END

#define __exist(fact, ...) FactPromiseHelper<ExistPromise, fact>(fact(__VA_ARGS__))
#define __not_exist(fact, ...) FactPromiseHelper<NotExistPromise, fact>(fact(__VA_ARGS__))

#endif
