#include <muse/promise/CompositePromise.h>

MUSE_NS_BEGIN

CompositePromise::CompositePromise(std::initializer_list<Promise*> promises)
: promises(promises)
{
}

void CompositePromise::addPromise(Promise& promise)
{
    promises.push_back(&promise);
}


MUSE_NS_END
