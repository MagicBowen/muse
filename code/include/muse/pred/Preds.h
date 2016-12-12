#ifndef H2B432465_F017_4316_810B_F5C4674B0FDD
#define H2B432465_F017_4316_810B_F5C4674B0FDD

#include <muse/pred/Pred.h>
#include <muse/base/StdExt.h>
#include <string>
#include <vector>

MUSE_NS_BEGIN

template<typename T>
struct Preds
{
    using PredType = Pred<T>;

    void addPred(PredType& pred)
    {
        preds.push_back(&pred);
    }

protected:
    bool pred(const T& value) const
    {
        bool result = true;
        for(auto p : preds)
        {
            if(!(*p)(value)) result = false;
        }
        return result;
    }

    std::string predInfo() const
    {
        if(preds.empty()) return std::string("predicate none");

        std::string info("predicate that ");
        foreach(preds, [&info](auto p){ info += (p->info() + std::string(";")); });
        return info;
    }

    void clear()
    {
        preds.clear();
    }

private:
    std::vector<PredType*> preds;
};

MUSE_NS_END

#endif
