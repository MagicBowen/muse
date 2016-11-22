#include <gtest/gtest.h>
#include <stubs/include/event/EventGenerator.h>
#include <stubs/include/runner/PromiseRunner.h>
#include <muse/promise/ExistPromise.h>
#include <muse/promise/NotExistPromise.h>
#include <muse/promise/SequentialPromise.h>
#include <muse/promise/ConcurrentPromise.h>
#include <muse/fact/FactAnd.h>
#include <muse/fact/FactOr.h>
#include <stubs/include/fact/CollisionFact.h>
#include <stubs/include/fact/DistanceLessFact.h>
#include <stubs/include/fact/StopFact.h>
#include <stubs/include/fact/DurationFact.h>
#include <stubs/include/event/FakeEvent.h>
#include <muse/promise/OptionalPromise.h>
#include <muse/promise/DaemonPromise.h>

USING_MUSE_NS;

struct TestPromise : testing::Test
{
    void prepareEvents(std::initializer_list<FakeEvent> events)
    {
        generator.generate(events);
    }

    bool verify(Promise& promise, unsigned int durationSeconds = 100)
    {
        promiseRunner.setPromise(promise);
        promiseRunner.setDuration(durationSeconds);
        promiseRunner.run();
        return promiseRunner.isSuccess();
    }

protected:
    EventGenerator generator;
    PromiseRunner promiseRunner{generator};
};

TEST_F(TestPromise, should_promise_success_when_fact_is_confirmed)
{
    prepareEvents({E_COLLISION()});

    CollisionFact fact;
    ExistPromise promise(fact);

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_promise_fail_when_fact_is_not_confirmed)
{
    prepareEvents({E_NOTHING()});

    CollisionFact fact;
    NotExistPromise promise(fact);

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_promise_success_when_all_of_fact_is_confirmed)
{
    prepareEvents({E_COLLISION(), E_NOTHING(), E_DISTANCE(5)});

    CollisionFact collision;
    DistanceLessFact distance(10);
    FactAnd fact({&collision, &distance});
    ExistPromise promise(fact);

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_promise_success_when_one_of_fact_is_confirmed)
{
    prepareEvents({E_NOTHING(), E_DISTANCE(5), E_COLLISION()});

    CollisionFact collision;
    DistanceLessFact distance(10);
    FactOr fact({&collision, &distance});
    ExistPromise promise(fact);

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_fail_when_timeout)
{
    prepareEvents({E_NOTHING(), E_DISTANCE(5), E_COLLISION()});

    CollisionFact fact;
    ExistPromise promise(fact);

    ASSERT_FALSE(verify(promise, 2));
}

TEST_F(TestPromise, should_sequential_promise_success_when_all_promise_success)
{
    prepareEvents({E_SPEED(5), E_DISTANCE(5), E_SPEED(0), E_DISTANCE(4)});

    StopFact stop;
    DistanceLessFact distance(5);

    ExistPromise existStop(stop);
    ExistPromise existDistance(distance);

    SequentialPromise promise({&existStop, &existDistance});

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_sequential_promise_fail_when_one_of_promise_fail)
{
    prepareEvents({E_SPEED(5), E_DISTANCE(5), E_SPEED(0), E_DISTANCE(5)});

    StopFact stop;
    DistanceLessFact distance(5);

    ExistPromise existStop(stop);
    ExistPromise existDistance(distance);

    SequentialPromise promise({&existStop, &existDistance});

    ASSERT_FALSE(verify(promise));
}

TEST_F(TestPromise, should_not_confirm_event_when_promise_in_sequential_not_started)
{
    prepareEvents({E_SPEED(5), E_DISTANCE(4), E_SPEED(0)});

    StopFact stop;
    DistanceLessFact distance(5);

    ExistPromise existStop(stop);
    ExistPromise existDistance(distance);

    SequentialPromise promise({&existStop, &existDistance});

    ASSERT_FALSE(verify(promise));
}

TEST_F(TestPromise, should_sequential_promise_fail_when_timeout)
{
    prepareEvents({E_SPEED(5), E_SPEED(0), E_DISTANCE(4)});

    StopFact stop;
    DistanceLessFact distance(5);

    ExistPromise existStop(stop);
    ExistPromise existDistance(distance);

    SequentialPromise promise({&existStop, &existDistance});

    ASSERT_FALSE(verify(promise, 2));
}

TEST_F(TestPromise, should_sequential_promise_fail_when_the_last_not_exist_promise_not_success)
{
    prepareEvents({E_SPEED(5), E_SPEED(0), E_COLLISION()});

    StopFact stop;
    CollisionFact collision;

    ExistPromise existStop(stop);
    NotExistPromise notExistCollision(collision);

    SequentialPromise promise({&existStop, &notExistCollision});

    ASSERT_FALSE(verify(promise));
}

TEST_F(TestPromise, should_sequential_promise_success_when_the_last_not_exist_promise_success)
{
    prepareEvents({E_SPEED(5), E_SPEED(0), E_NOTHING()});

    StopFact stop;
    CollisionFact collision;

    ExistPromise existStop(stop);
    NotExistPromise notExistCollision(collision);

    SequentialPromise promise({&existStop, &notExistCollision});

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_concurrent_promise_success_when_all_exist_promise_success)
{
    prepareEvents({E_SPEED(5), E_SPEED(0), E_COLLISION()});

    StopFact stop;
    CollisionFact collision;

    ExistPromise existStop(stop);
    ExistPromise existCollision(collision);

    ConcurrentPromise promise({&existStop, &existCollision});

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_concurrent_promise_fail_when_any_of_exist_promise_fail)
{
    prepareEvents({E_SPEED(1), E_COLLISION()});

    StopFact stop;
    CollisionFact collision;

    ExistPromise existStop(stop);
    ExistPromise existCollision(collision);

    ConcurrentPromise promise({&existStop, &existCollision});

    ASSERT_FALSE(verify(promise));
}

TEST_F(TestPromise, should_concurrent_promise_success_when_the_not_exist_promise_success)
{
    prepareEvents({E_SPEED(0), E_NOTHING()});

    StopFact stop;
    CollisionFact collision;

    ExistPromise existStop(stop);
    NotExistPromise notExistCollision(collision);

    ConcurrentPromise promise({&existStop, &notExistCollision});

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_optional_promise_success_when_any_promise_success)
{
    prepareEvents({E_SPEED(1), E_COLLISION()});

    StopFact stop;
    CollisionFact collision;

    ExistPromise existStop(stop);
    ExistPromise existCollision(collision);

    OptionalPromise promise({&existStop, &existCollision});

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_promise_fail_when_the_daemon_promise_fail)
{
    prepareEvents({E_SPEED(1), E_COLLISION()});

    StopFact stop;
    CollisionFact collision;

    ExistPromise existStop(stop);
    NotExistPromise notExistCollision(collision);

    DaemonPromise promise(notExistCollision, existStop);

    ASSERT_FALSE(verify(promise));
}

TEST_F(TestPromise, should_promise_success_when_the_not_daemon_promise_success)
{
    prepareEvents({E_SPEED(0), E_NOTHING()});

    StopFact stop;
    CollisionFact collision;

    ExistPromise existStop(stop);
    ExistPromise existCollision(collision);

    DaemonPromise promise(existCollision, existStop);

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_optional_promise_fail_when_all_promise_fail)
{
    prepareEvents({E_SPEED(1), E_COLLISION()});

    StopFact stop;
    CollisionFact collision;

    ExistPromise existStop(stop);
    NotExistPromise notExistCollision(collision);

    OptionalPromise promise({&existStop, &notExistCollision});

    ASSERT_FALSE(verify(promise));
}

TEST_F(TestPromise, should_composed_promise_success_when_all_promise_success)
{
    prepareEvents({E_DISTANCE(11),
                   E_SPEED(0),
                   E_DISTANCE(9),
                   E_NOTHING(),
                   E_SPEED(1)});

    CollisionFact collision;
    NotExistPromise notExistCollision(collision);

    DistanceLessFact distance(10);
    StopFact stop;
    DurationFact duration(2);

    ExistPromise existDistance(distance);
    NotExistPromise notExistStop(stop);
    ExistPromise existDuration(duration);

    ConcurrentPromise notStop_and_duration({&notExistStop, &existDuration});
    SequentialPromise inDistance_then_notStop_and_duration({&existDistance, &notStop_and_duration});
    ConcurrentPromise promise({&notExistCollision, &inDistance_then_notStop_and_duration});

    ASSERT_TRUE(verify(promise));
}
