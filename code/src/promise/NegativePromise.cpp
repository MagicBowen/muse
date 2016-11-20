#include <muse/promise/NegativePromise.h>

MUSE_NS_BEGIN

NegativePromise::NegativePromise(Promise& validator)
: promise(validator)
{
}

void NegativePromise::start()
{
    promise.start();
}

void NegativePromise::stop()
{
    promise.stop();
}

void NegativePromise::onEvent(const Event& event)
{
    promise.onEvent(event);
}

Result NegativePromise::evaluate() const
{
    return negativeOf(promise.evaluate());
}

MUSE_NS_END
