#include <muse/fact/CollisionFact.h>
#include <muse/validator/ExistValidator.h>
#include <muse/validator/NotExistValidator.h>
#include <muse/event/Event.h>
#include <muse/base/Log.h>

USING_MUSE_NS;

int main(int argc, char** argv)
{
    Result result;
    CollisionFact fact;
    ExistValidator validator{fact};
    NotExistValidator notValiator(fact);

    Validator& v = notValiator;

    v.onEvent(Event{COLLISION, 0.0});

    result = v.evaluate();
    INFO_LOG("result = %d", result);

    v.start();
    v.onEvent(Event{NOTHING, 0.0});

    v.stop();
    v.onEvent(Event{COLLISION, 0.0});

    result = v.evaluate();
    INFO_LOG("result = %d", result);

    return 0;
}
