#include <gtest/gtest.h>
#include <muse/dsl/PromiseDsl.h>
#include <stubs/include/event/EventGenerator.h>
#include <stubs/include/runner/PromiseRunner.h>
#include <stubs/include/fact/Collision.h>
#include <stubs/include/fact/Distance.h>
#include <stubs/include/fact/Stop.h>
#include <stubs/include/fact/Duration.h>
#include <stubs/include/event/FakeEvent.h>
#include <muse/dsl/helper/ClosureFactHelper.h>

USING_MUSE_NS;

namespace
{
    struct LessThan
    {
        LessThan(double bound) : bound(bound)
        {
        }

        bool operator()(double value) const
        {
            return value < bound;
        }

    private:
        double bound;
    };

    struct MoreThan
    {
        MoreThan(double bound) : bound(bound)
        {
        }

        bool operator()(double value) const
        {
            return value > bound;
        }

    private:
        double bound;
    };

    struct EqualTo
    {
        EqualTo(double bound) : bound(bound)
        {
        }

        bool operator()(double value) const
        {
            return value == bound;
        }

    private:
        double bound;
    };
}

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

    auto promise = __exist(__all(Collision(), Distance(LessThan(10))));

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_promise_success_when_one_of_fact_is_confirmed)
{
    prepareEvents({E_NOTHING(), E_DISTANCE(15), E_COLLISION()});

    auto promise = __exist(__any(Collision(), Distance(LessThan(10))));

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_evaluate_in_end_when_declare_closure_fact)
{
    prepareEvents({E_DISTANCE(0), E_DISTANCE(10)});

    auto promise = __exist(__closure(Distance(LessThan(10))));

    ASSERT_FALSE(verify(promise));
}

TEST_F(TestPromise, should_evaluate_in_end_when_until_promise_occurred)
{
    prepareEvents({E_DISTANCE(0), E_DISTANCE(5), E_DISTANCE(10)});

    auto promise = __until(__exist(Duration(EqualTo(2))), __exist(__closure(Distance(LessThan(10)))));

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_fail_when_timeout)
{
    prepareEvents({E_NOTHING(), E_DISTANCE(5), E_COLLISION()});

    auto promise = __exist(Collision());

    ASSERT_FALSE(verify(promise, 2));
}

TEST_F(TestPromise, should_sequential_promise_success_when_all_promise_success)
{
    prepareEvents({E_SPEED(5), E_DISTANCE(5), E_SPEED(0), E_DISTANCE(4)});

    auto promise = __seq(__exist(Stop()), __exist(Distance(LessThan(5))));

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_sequential_promise_fail_when_one_of_promise_fail)
{
    prepareEvents({E_SPEED(5), E_DISTANCE(5), E_SPEED(0), E_DISTANCE(5)});

    auto promise = __seq(__exist(Stop()), __exist(Distance(LessThan(5))));

    ASSERT_FALSE(verify(promise));
}

TEST_F(TestPromise, should_not_confirm_event_when_promise_in_sequential_not_started)
{
    prepareEvents({E_SPEED(5), E_DISTANCE(4), E_SPEED(0)});

    auto promise = __seq(__exist(Stop()), __exist(Distance(LessThan(5))));

    ASSERT_FALSE(verify(promise));
}

TEST_F(TestPromise, should_sequential_promise_fail_when_timeout)
{
    prepareEvents({E_SPEED(5), E_SPEED(0), E_DISTANCE(4)});

    auto promise = __seq(__exist(Stop()), __exist(Distance(LessThan(5))));

    ASSERT_FALSE(verify(promise, 2));
}

TEST_F(TestPromise, should_sequential_promise_fail_when_the_last_not_exist_promise_not_success)
{
    prepareEvents({E_SPEED(5), E_SPEED(0), E_COLLISION()});

    auto promise = __seq(__exist(Stop()), __not_exist(Collision()));

    ASSERT_FALSE(verify(promise));
}

TEST_F(TestPromise, should_sequential_promise_success_when_the_last_not_exist_promise_success)
{
    prepareEvents({E_SPEED(5), E_SPEED(0), E_NOTHING()});

    auto promise = __seq(__exist(Stop()), __not_exist(Collision()));

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_concurrent_promise_success_when_all_exist_promise_success)
{
    prepareEvents({E_SPEED(5), E_SPEED(0), E_COLLISION()});

    auto promise = __con(__exist(Stop()), __exist(Collision()));

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_concurrent_promise_fail_when_any_of_exist_promise_fail)
{
    prepareEvents({E_SPEED(1), E_COLLISION()});

    auto promise = __con(__exist(Stop()), __exist(Collision()));

    ASSERT_FALSE(verify(promise));
}

TEST_F(TestPromise, should_concurrent_promise_success_when_the_not_exist_promise_success)
{
    prepareEvents({E_SPEED(0), E_NOTHING()});

    auto promise = __con(__exist(Stop()), __not_exist(Collision()));

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_optional_promise_success_when_any_promise_success)
{
    prepareEvents({E_SPEED(1), E_COLLISION()});

    auto promise = __opt(__exist(Stop()), __exist(Collision()));

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_promise_fail_when_the_daemon_promise_fail)
{
    prepareEvents({E_DISTANCE(5), E_COLLISION()});

    auto promise = __daemon(__not_exist(Collision()), __exist(Distance(LessThan(4))));

    ASSERT_FALSE(verify(promise));
}

TEST_F(TestPromise, should_promise_success_when_the_not_daemon_promise_success)
{
    prepareEvents({E_SPEED(0), E_NOTHING()});

    auto promise = __daemon(__exist(Collision()), __exist(Stop()));

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_promise_success_when_the_daemon_promise_be_stopped)
{
    prepareEvents({E_NOTHING(), E_NOTHING()});

    auto promise = __daemon(__not_exist(Stop()), __not_exist(Collision()));

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_promise_fix_when_until_promise_fix)
{
    prepareEvents({E_DISTANCE(4), E_DISTANCE(3), E_DISTANCE(2), E_DISTANCE(1)});

    auto promise = __until(__exist(Duration(MoreThan(2))), __not_exist(Distance(LessThan(2))));

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_promise_success_when_until_promise_terminate)
{
    prepareEvents({E_NOTHING(), E_SPEED(1), E_COLLISION()});

    auto promise = __until(__exist(Stop()), __exist(Collision()));

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
    prepareEvents({E_DISTANCE(11), E_SPEED(0), E_DISTANCE(9), E_NOTHING(), E_SPEED(1)});

    auto promise = __con( __not_exist(Collision())
                        , __seq( __exist(Distance(LessThan(10)))
                               , __con( __not_exist(Stop())
                                      , __exist(Duration(MoreThan(1))))));

    ASSERT_TRUE(verify(promise));
}
