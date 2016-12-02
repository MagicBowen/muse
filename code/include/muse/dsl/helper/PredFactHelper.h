#ifndef H76C94BBB_0F55_4E9C_9BA0_F977665776D8
#define H76C94BBB_0F55_4E9C_9BA0_F977665776D8

#include <muse/pred/PredAdaper.h>
#include <memory>

MUSE_NS_BEGIN

template<typename FACT>
struct PredFactHelper : FACT
{
    using FACT::FACT;

    template<typename PRED>
    PredFactHelper& predOf(PRED&& p)
    {
        pred.reset(new PredAdapter<std::decay_t<PRED>, typename FACT::PredType>(std::forward<PRED>(p)));
        this->addPred(*(pred.get()));
        return *this;
    }

private:
    std::shared_ptr<Pred<typename FACT::PredType>> pred;
};

MUSE_NS_END

#define __fact(name, ...)  ::MUSE_NS::PredFactHelper<name>(__VA_ARGS__)

#endif
