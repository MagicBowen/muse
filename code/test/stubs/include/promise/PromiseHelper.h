#ifndef H8191557C_DB50_4576_89D5_6DAD7D234FFB
#define H8191557C_DB50_4576_89D5_6DAD7D234FFB

#include <muse/muse.h>

MUSE_NS_BEGIN

template<typename PROMISE, typename FACT>
struct FactPromiseHelper : PROMISE
{
    FactPromiseHelper() : PROMISE(fact){}
private:
    FACT fact;
};

template<typename ...PROMISES> struct SequentialPromiseHelper;

template<typename PROMISE, typename ...OTHERS>
struct SequentialPromiseHelper<PROMISE, OTHERS...>
: SequentialPromiseHelper<OTHERS...>
{
    SequentialPromiseHelper()
    {
        this->addPromise(promise);
    }

private:
    PROMISE promise;
};

template<>
struct SequentialPromiseHelper<> : SequentialPromise
{
};

template<typename ...PROMISES> struct OptionalPromiseHelper;

template<typename PROMISE, typename ...OTHERS>
struct OptionalPromiseHelper<PROMISE, OTHERS...>
: OptionalPromiseHelper<OTHERS...>
{
    OptionalPromiseHelper()
    {
        this->addPromise(promise);
    }

private:
    PROMISE promise;
};

template<>
struct OptionalPromiseHelper<> : OptionalPromise
{
};


MUSE_NS_END

#define __exist(...)      FactPromiseHelper<ExistPromise, __VA_ARGS__>
#define __not_exist(...)  FactPromiseHelper<NotExistPromise, __VA_ARGS__>
#define __sequential(...) SequentialPromiseHelper<__VA_ARGS__>
#define __optional(...)   OptionalPromiseHelper<__VA_ARGS__>

#define __def_promise(name, ...) using name = __VA_ARGS__

#endif
