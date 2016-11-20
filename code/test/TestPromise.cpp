#include <gtest/gtest.h>
#include <stubs/include/EventGenerator.h>
#include <muse/event/Event.h>
#include <muse/simulation/Simulation.h>
#include <muse/promise/ExistPromise.h>
#include <muse/promise/NotExistPromise.h>
#include <muse/promise/SequentialPromise.h>
#include <muse/fact/core/AllOfFact.h>
#include <muse/fact/core/AnyOfFact.h>
#include <muse/fact/CollisionFact.h>
#include <muse/fact/DistanceLessFact.h>
#include <muse/fact/StopFact.h>

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

protected:
    Simulation simulation;
    EventGenerator generator;
};

TEST_F(TestPromise, should_promise_exist_when_fact_is_confirmed)
{
    prepareEvent(COLLISION);

    CollisionFact fact;
    ExistPromise promise(fact);

    simulation.setPromise(promise);
    simulation.play();

    ASSERT_TRUE(simulation.isSuccess());
}

TEST_F(TestPromise, should_promise_no_exist_when_fact_is_not_confirmed)
{
    prepareEvent(NOTHING);

    CollisionFact fact;
    NotExistPromise promise(fact);

    simulation.setPromise(promise);
    simulation.play();

    ASSERT_TRUE(simulation.isSuccess());
}

TEST_F(TestPromise, should_promise_exist_when_all_of_fact_is_confirmed)
{
    prepareEvents({Event(COLLISION, 0), Event(NOTHING), Event(DISTANCE, 5)});

    CollisionFact collision;
    DistanceLessFact distance(10);
    AllOfFact fact({&collision, &distance});
    ExistPromise promise(fact);

    simulation.setPromise(promise);
    simulation.play();

    ASSERT_TRUE(simulation.isSuccess());
}

TEST_F(TestPromise, should_promise_exist_when_one_of_fact_is_confirmed)
{
    prepareEvents({Event(NOTHING), Event(DISTANCE, 5), Event(COLLISION)});

    CollisionFact collision;
    DistanceLessFact distance(10);
    AnyOfFact fact({&collision, &distance});
    ExistPromise promise(fact);

    simulation.setPromise(promise);
    simulation.play();

    ASSERT_TRUE(simulation.isSuccess());
}

TEST_F(TestPromise, should_fail_when_timeout)
{
    prepareEvents({Event(NOTHING), Event(DISTANCE, 5), Event(COLLISION)});

    CollisionFact fact;
    ExistPromise promise(fact);

    simulation.setPromise(promise);
    simulation.setDuration(2);
    simulation.play();

    ASSERT_FALSE(simulation.isSuccess());
}

TEST_F(TestPromise, should_promise_exist_when_fact_confirmed_one_by_one)
{
    prepareEvents({Event(DISTANCE, 10), Event(SPEED, 5), Event(DISTANCE, 5), Event(SPEED, 0), Event(DISTANCE, 4)});

    StopFact stop;
    DistanceLessFact distance(5);

    ExistPromise existStop(stop);
    ExistPromise existDistance(distance);

    SequentialPromise promise({&existStop, &existDistance});

    simulation.setPromise(promise);
    simulation.play();

    ASSERT_TRUE(simulation.isSuccess());
}
