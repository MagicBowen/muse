#ifndef H4FC1FE68_BF4F_4CE3_9453_17A7DF9CDE19
#define H4FC1FE68_BF4F_4CE3_9453_17A7DF9CDE19

#include <muse/fact/BaseFact.h>
#include <list>

MUSE_NS_BEGIN

struct CompositeFact : BaseFact
{
    void addFact(Fact&);

private:
    OVERRIDE(void onStarted());
    OVERRIDE(void onStopped());

protected:
    std::list<Fact*> facts;
};

MUSE_NS_END

#endif
