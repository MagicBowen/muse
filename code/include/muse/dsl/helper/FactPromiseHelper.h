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

    FactPromiseHelper(const FactPromiseHelper& rhs)
    : PROMISE(fact), fact(rhs.fact)
    {
    }

    FactPromiseHelper(FACT&& f)
    : PROMISE(fact), fact(std::move(f))
    {
    }

    FactPromiseHelper(FactPromiseHelper&& rhs)
    : PROMISE(fact), fact(std::move(rhs.fact))
    {
    }

private:
    FACT fact;
};

MUSE_NS_END

#define __exist(...)     ::MUSE_NS::FactPromiseHelper<ExistPromise, std::decay_t<decltype(__VA_ARGS__)>>(__VA_ARGS__)
#define __not_exist(...) ::MUSE_NS::FactPromiseHelper<NotExistPromise, std::decay_t<decltype(__VA_ARGS__)>>(__VA_ARGS__)

#endif
