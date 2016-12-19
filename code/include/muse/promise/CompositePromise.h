#ifndef H6C9671B8_29A5_4227_ABC7_72D6E8A8CD7C
#define H6C9671B8_29A5_4227_ABC7_72D6E8A8CD7C

#include <muse/promise/Promise.h>
#include <list>

MUSE_NS_BEGIN

struct CompositePromise : Promise
{
    void clear();
    void addPromise(Promise&);

private:
    DEFAULT(void, reset());

protected:
    using Promises = std::list<Promise*>;
    std::list<Promise*> promises;
};

MUSE_NS_END

#endif
