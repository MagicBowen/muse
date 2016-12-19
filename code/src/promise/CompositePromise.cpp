#include <muse/promise/CompositePromise.h>

MUSE_NS_BEGIN

void CompositePromise::clear()
{
    promises.clear();
}

void CompositePromise::addPromise(Promise& promise)
{
    promises.push_back(&promise);
    if(promises.size() == 1) reset();
}


MUSE_NS_END
