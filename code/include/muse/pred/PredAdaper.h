#ifndef HC08D322B_01ED_4BA9_B4E5_FB98FC352997
#define HC08D322B_01ED_4BA9_B4E5_FB98FC352997

#include <muse/pred/Pred.h>

MUSE_NS_BEGIN

template<typename PRED, typename T>
struct PredAdapter : Pred<T>
{
    PredAdapter(const PRED& pred)
    : p(pred)
    {
    }

    PredAdapter(PRED&& pred)
    : p(std::move(pred))
    {
    }

private:
    OVERRIDE(bool operator()(const T& value) const)
    {
        return p(value);
    }

    OVERRIDE(std::string info() const)
    {
        return p.info();
    }

private:
    PRED p;
};

MUSE_NS_END

#endif
