#include <gtest/gtest.h>
#include <muse/dsl/PromiseDsl.h>
#include <stubs/include/event/EventGenerator.h>
#include <stubs/include/runner/PromiseRunner.h>
#include <stubs/include/fact/Collision.h>
#include <stubs/include/fact/Distance.h>
#include <stubs/include/fact/Stop.h>
#include <stubs/include/fact/Duration.h>
#include <stubs/include/event/FakeEvent.h>

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

    auto promise = __exist(Collision());

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_promise_fail_when_fact_is_not_confirmed)
{
    prepareEvents({E_NOTHING()});

    auto promise = __not_exist(Collision());

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_promise_success_when_all_of_fact_is_confirmed)
{
    prepareEvents({E_COLLISION(), E_NOTHING(), E_DISTANCE(5)});

    auto lessThan10 = [](double value){return value < 10;};
    auto promise = __exist(__all(Collision(), Distance(lessThan10)));

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_promise_success_when_one_of_fact_is_confirmed)
{
    prepareEvents({E_NOTHING(), E_DISTANCE(5), E_COLLISION()});

    Collision collision;
    Distance distance([](double value){return value < 10;});
    FactAny fact({&collision, &distance});
    ExistPromise promise(fact);

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_fail_when_timeout)
{
    prepareEvents({E_NOTHING(), E_DISTANCE(5), E_COLLISION()});

    Collision fact;
    ExistPromise promise(fact);

    ASSERT_FALSE(verify(promise, 2));
}

TEST_F(TestPromise, should_sequential_promise_success_when_all_promise_success)
{
    prepareEvents({E_SPEED(5), E_DISTANCE(5), E_SPEED(0), E_DISTANCE(4)});

    Stop stop;
    Distance distance([](double value){return value < 5;});

    ExistPromise existStop(stop);
    ExistPromise existDistance(distance);

    SequentialPromise promise({&existStop, &existDistance});

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_sequential_promise_fail_when_one_of_promise_fail)
{
    prepareEvents({E_SPEED(5), E_DISTANCE(5), E_SPEED(0), E_DISTANCE(5)});

    Stop stop;
    Distance distance([](double value){return value < 5;});

    ExistPromise existStop(stop);
    ExistPromise existDistance(distance);

    SequentialPromise promise({&existStop, &existDistance});

    ASSERT_FALSE(verify(promise));
}

TEST_F(TestPromise, should_not_confirm_event_when_promise_in_sequential_not_started)
{
    prepareEvents({E_SPEED(5), E_DISTANCE(4), E_SPEED(0)});

    Stop stop;
    Distance distance([](double value){return value < 5;});

    ExistPromise existStop(stop);
    ExistPromise existDistance(distance);

    SequentialPromise promise({&existStop, &existDistance});

    ASSERT_FALSE(verify(promise));
}

TEST_F(TestPromise, should_sequential_promise_fail_when_timeout)
{
    prepareEvents({E_SPEED(5), E_SPEED(0), E_DISTANCE(4)});

    Stop stop;
    Distance distance([](double value){return value < 5;});

    ExistPromise existStop(stop);
    ExistPromise existDistance(distance);

    SequentialPromise promise({&existStop, &existDistance});

    ASSERT_FALSE(verify(promise, 2));
}

TEST_F(TestPromise, should_sequential_promise_fail_when_the_last_not_exist_promise_not_success)
{
    prepareEvents({E_SPEED(5), E_SPEED(0), E_COLLISION()});

    Stop stop;
    Collision collision;

    ExistPromise existStop(stop);
    NotExistPromise notExistCollision(collision);

    SequentialPromise promise({&existStop, &notExistCollision});

    ASSERT_FALSE(verify(promise));
}

TEST_F(TestPromise, should_sequential_promise_success_when_the_last_not_exist_promise_success)
{
    prepareEvents({E_SPEED(5), E_SPEED(0), E_NOTHING()});

    Stop stop;
    Collision collision;

    ExistPromise existStop(stop);
    NotExistPromise notExistCollision(collision);

    SequentialPromise promise({&existStop, &notExistCollision});

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_concurrent_promise_success_when_all_exist_promise_success)
{
    prepareEvents({E_SPEED(5), E_SPEED(0), E_COLLISION()});

    Stop stop;
    Collision collision;

    ExistPromise existStop(stop);
    ExistPromise existCollision(collision);

    ConcurrentPromise promise({&existStop, &existCollision});

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_concurrent_promise_fail_when_any_of_exist_promise_fail)
{
    prepareEvents({E_SPEED(1), E_COLLISION()});

    Stop stop;
    Collision collision;

    ExistPromise existStop(stop);
    ExistPromise existCollision(collision);

    ConcurrentPromise promise({&existStop, &existCollision});

    ASSERT_FALSE(verify(promise));
}

TEST_F(TestPromise, should_concurrent_promise_success_when_the_not_exist_promise_success)
{
    prepareEvents({E_SPEED(0), E_NOTHING()});

    Stop stop;
    Collision collision;

    ExistPromise existStop(stop);
    NotExistPromise notExistCollision(collision);

    ConcurrentPromise promise({&existStop, &notExistCollision});

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_optional_promise_success_when_any_promise_success)
{
    prepareEvents({E_SPEED(1), E_COLLISION()});

    Stop stop;
    Collision collision;

    ExistPromise existStop(stop);
    ExistPromise existCollision(collision);

    OptionalPromise promise({&existStop, &existCollision});

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_promise_fail_when_the_daemon_promise_fail)
{
    prepareEvents({E_DISTANCE(5), E_COLLISION()});

    auto lessThan4 = [](double v) {return v < 4;};
    auto promise = __daemon(__not_exist(Collision()), __exist(Distance(lessThan4)));

    ASSERT_FALSE(verify(promise));
}

TEST_F(TestPromise, should_promise_success_when_the_not_daemon_promise_success)
{
    prepareEvents({E_SPEED(0), E_NOTHING()});

    auto promise = __daemon(__exist(Collision()), __exist(Stop()));

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_optional_promise_fail_when_all_promise_fail)
{
    prepareEvents({E_SPEED(1), E_COLLISION()});

    auto promise = __opt(__exist(Stop()), __not_exist(Collision()));

    ASSERT_FALSE(verify(promise));
}

TEST_F(TestPromise, should_composed_promise_success_when_all_promise_success)
{
    prepareEvents({E_DISTANCE(11),
                   E_SPEED(0),
                   E_DISTANCE(9),
                   E_NOTHING(),
                   E_SPEED(1)});

    Collision collision;
    NotExistPromise notExistCollision(collision);

    Distance distance([](double value){return value < 10;});
    Stop stop;

    unsigned int time = 1;
    Duration duration([time](double value){return value > time;});

    ExistPromise existDistance(distance);
    NotExistPromise notExistStop(stop);
    ExistPromise existDuration(duration);

    ConcurrentPromise notStop_and_duration({&notExistStop, &existDuration});
    SequentialPromise inDistance_then_notStop_and_duration({&existDistance, &notStop_and_duration});
    ConcurrentPromise promise({&notExistCollision, &inDistance_then_notStop_and_duration});

    ASSERT_TRUE(verify(promise));
}
