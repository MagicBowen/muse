#include <gtest/gtest.h>
#include <stubs/include/EventGenerator.h>
#include <muse/event/Event.h>
#include <muse/simulation/Simulation.h>
#include <muse/promise/ExistPromise.h>
#include <muse/promise/NotExistPromise.h>
#include <muse/promise/SequentialPromise.h>
#include <muse/promise/ConcurrentPromise.h>
#include <muse/fact/core/AllOfFact.h>
#include <muse/fact/core/AnyOfFact.h>
#include <muse/fact/CollisionFact.h>
#include <muse/fact/DistanceLessFact.h>
#include <muse/fact/StopFact.h>
#include <muse/fact/DurationFact.h>

USING_MUSE_NS;

struct TestPromise : testing::Test
{
    void prepareEvent(EventType type, double value = 0)
    {
        generator.generate(type, value);
    }

    void prepareEvents(std::initializer_list<Event> events)
    {
        for(auto event : events)
        {
            prepareEvent(event.type, event.value);
        }
    }

    bool verify(Promise& promise, unsigned int durationSeconds = 100)
    {
        simulation.setPromise(promise);
        simulation.setDuration(durationSeconds);
        simulation.play();
        return simulation.isSuccess();
    }

protected:
    Simulation simulation;
    EventGenerator generator;
};

TEST_F(TestPromise, should_promise_success_when_fact_is_confirmed)
{
    prepareEvent(COLLISION);

    CollisionFact fact;
    ExistPromise promise(fact);

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_promise_fail_when_fact_is_not_confirmed)
{
    prepareEvent(NOTHING);

    CollisionFact fact;
    NotExistPromise promise(fact);

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_promise_success_when_all_of_fact_is_confirmed)
{
    prepareEvents({Event(COLLISION, 0), Event(NOTHING), Event(DISTANCE, 5)});

    CollisionFact collision;
    DistanceLessFact distance(10);
    AllOfFact fact({&collision, &distance});
    ExistPromise promise(fact);

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_promise_success_when_one_of_fact_is_confirmed)
{
    prepareEvents({Event(NOTHING), Event(DISTANCE, 5), Event(COLLISION)});

    CollisionFact collision;
    DistanceLessFact distance(10);
    AnyOfFact fact({&collision, &distance});
    ExistPromise promise(fact);

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_fail_when_timeout)
{
    prepareEvents({Event(NOTHING), Event(DISTANCE, 5), Event(COLLISION)});

    CollisionFact fact;
    ExistPromise promise(fact);

    ASSERT_FALSE(verify(promise, 2));
}

TEST_F(TestPromise, should_sequential_promise_success_when_all_promise_success)
{
    prepareEvents({Event(SPEED, 5), Event(DISTANCE, 5), Event(SPEED, 0), Event(DISTANCE, 4)});

    StopFact stop;
    DistanceLessFact distance(5);

    ExistPromise existStop(stop);
    ExistPromise existDistance(distance);

    SequentialPromise promise({&existStop, &existDistance});

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_sequential_promise_fail_when_one_of_promise_fail)
{
    prepareEvents({Event(SPEED, 5), Event(DISTANCE, 5), Event(SPEED, 0), Event(DISTANCE, 5)});

    StopFact stop;
    DistanceLessFact distance(5);

    ExistPromise existStop(stop);
    ExistPromise existDistance(distance);

    SequentialPromise promise({&existStop, &existDistance});

    ASSERT_FALSE(verify(promise));
}

TEST_F(TestPromise, should_not_confirm_event_when_promise_in_sequential_not_started)
{
    prepareEvents({Event(SPEED, 5), Event(DISTANCE, 4), Event(SPEED, 0)});

    StopFact stop;
    DistanceLessFact distance(5);

    ExistPromise existStop(stop);
    ExistPromise existDistance(distance);

    SequentialPromise promise({&existStop, &existDistance});

    ASSERT_FALSE(verify(promise));
}

TEST_F(TestPromise, should_sequential_promise_fail_when_timeout)
{
    prepareEvents({Event(SPEED, 5), Event(SPEED, 0), Event(DISTANCE, 4)});

    StopFact stop;
    DistanceLessFact distance(5);

    ExistPromise existStop(stop);
    ExistPromise existDistance(distance);

    SequentialPromise promise({&existStop, &existDistance});

    ASSERT_FALSE(verify(promise, 2));
}

TEST_F(TestPromise, should_sequential_promise_fail_when_the_last_not_exist_promise_not_success)
{
    prepareEvents({Event(SPEED, 5), Event(SPEED, 0), Event(COLLISION)});

    StopFact stop;
    CollisionFact collision;

    ExistPromise existStop(stop);
    NotExistPromise notExistCollision(collision);

    SequentialPromise promise({&existStop, &notExistCollision});

    ASSERT_FALSE(verify(promise));
}

TEST_F(TestPromise, should_sequential_promise_success_when_the_last_not_exist_promise_success)
{
    prepareEvents({Event(SPEED, 5), Event(SPEED, 0), Event(NOTHING)});

    StopFact stop;
    CollisionFact collision;

    ExistPromise existStop(stop);
    NotExistPromise notExistCollision(collision);

    SequentialPromise promise({&existStop, &notExistCollision});

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_concurrent_promise_success_when_all_exist_promise_success)
{
    prepareEvents({Event(SPEED, 5), Event(SPEED, 0), Event(COLLISION)});

    StopFact stop;
    CollisionFact collision;

    ExistPromise existStop(stop);
    ExistPromise existCollision(collision);

    ConcurrentPromise promise({&existStop, &existCollision});

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_concurrent_promise_fail_when_any_of_exist_promise_fail)
{
    prepareEvents({Event(SPEED, 1), Event(COLLISION)});

    StopFact stop;
    CollisionFact collision;

    ExistPromise existStop(stop);
    ExistPromise existCollision(collision);

    ConcurrentPromise promise({&existStop, &existCollision});

    ASSERT_FALSE(verify(promise));
}

TEST_F(TestPromise, should_concurrent_promise_success_when_the_not_exist_promise_success)
{
    prepareEvents({Event(SPEED, 0), Event(NOTHING)});

    StopFact stop;
    CollisionFact collision;

    ExistPromise existStop(stop);
    NotExistPromise notExistCollision(collision);

    ConcurrentPromise promise({&existStop, &notExistCollision});

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_composed_promise_success_when_all_promise_success)
{
    prepareEvents({Event(DISTANCE, 11),
                   Event(SPEED, 0),
                   Event(DISTANCE, 9),
                   Event(NOTHING),
                   Event(SPEED, 1)});

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
