#ifndef H605AFBE9_A257_4505_89F3_5BEF1E875008
#define H605AFBE9_A257_4505_89F3_5BEF1E875008

#include <muse/promise/ListenedPromise.h>
#include <tuple>

MUSE_NS_BEGIN

template<typename LISTENER, typename PROMISE>
struct ListenedPromiseHelper : ListenedPromise
{
    ListenedPromiseHelper(const LISTENER& listener, const PROMISE& p)
    : ListenedPromise(promise), promise(p), listener(listener)
    {
        this->addListener(this->listener);
    }

    ListenedPromiseHelper(const ListenedPromiseHelper& rhs)
    : ListenedPromise(promise), promise(rhs.promise), listener(rhs.listener)
    {
        this->addListener(this->listener);
    }

    ListenedPromiseHelper(LISTENER&& listener, PROMISE&& p)
    : ListenedPromise(promise), promise(std::move(p)), listener(std::move(listener))
    {
        this->addListener(this->listener);
    }

    ListenedPromiseHelper(ListenedPromiseHelper&& rhs)
    : ListenedPromise(promise), promise(std::move(rhs.promise)), listener(std::move(rhs.listener))
    {
        this->addListener(this->listener);
    }

private:
    PROMISE  promise;
    LISTENER listener;
};

MUSE_NS_END

#define __listen(LISTENER, PROMISE)     \
::MUSE_NS::ListenedPromiseHelper<std::decay_t<decltype(LISTENER)>, std::decay_t<decltype(PROMISE)>>(LISTENER, PROMISE)

#endif
