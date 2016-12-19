#include <gtest/gtest.h>
#include <muse/dsl/PromiseDsl.h>
#include <stubs/include/event/EventGenerator.h>
#include <stubs/include/runner/PromiseRunner.h>
#include <stubs/include/fact/Collision.h>
#include <stubs/include/fact/Distance.h>
#include <stubs/include/fact/Stop.h>
#include <stubs/include/fact/Duration.h>
#include <stubs/include/event/FakeEvent.h>
#include <stubs/include/pred/LessThan.h>
#include <stubs/include/pred/GreaterThan.h>
#include <stubs/include/pred/EqualTo.h>
#include <muse/listener/PromiseListener.h>

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

    auto promise = __exist(__fact(Collision));

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_promise_fail_when_fact_is_not_confirmed)
{
    prepareEvents({E_NOTHING()});

    auto promise = __not_exist(__fact(Collision));

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_evaluate_in_end_when_declare_closure_fact)
{
    prepareEvents({E_DISTANCE(0), E_DISTANCE(10)});

    auto promise = __exist(__closure(__fact(Distance).predOf(LessThan<double>(10))));

    ASSERT_FALSE(verify(promise));
}

TEST_F(TestPromise, should_evaluate_in_end_when_until_promise_occurred)
{
    prepareEvents({E_DISTANCE(0), E_DISTANCE(5), E_DISTANCE(10)});

    auto promise = __until( __exist(__fact(Duration).predOf(EqualTo<unsigned int>(2)))
                          , __exist(__closure(__fact(Distance).predOf(LessThan<double>(10)))));

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_fail_when_timeout)
{
    prepareEvents({E_NOTHING(), E_DISTANCE(5), E_COLLISION()});

    auto promise = __exist(__fact(Collision));

    ASSERT_FALSE(verify(promise, 2));
}

TEST_F(TestPromise, should_sequential_promise_success_when_all_promise_success)
{
    prepareEvents({E_SPEED(5), E_DISTANCE(5), E_SPEED(0), E_DISTANCE(4)});

    auto promise = __seq( __exist(__fact(Stop))
                        , __exist(__fact(Distance).predOf(LessThan<double>(5))));

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_sequential_promise_fail_when_one_of_promise_fail)
{
    prepareEvents({E_SPEED(5), E_DISTANCE(5), E_SPEED(0), E_DISTANCE(5)});

    auto promise = __seq( __exist(__fact(Stop))
                        , __exist(__fact(Distance).predOf(LessThan<double>(5))));

    ASSERT_FALSE(verify(promise));
}

TEST_F(TestPromise, should_not_confirm_event_when_promise_in_sequential_not_started)
{
    prepareEvents({E_SPEED(5), E_DISTANCE(4), E_SPEED(0)});

    auto promise = __seq(__exist(__fact(Stop)), __exist(__fact(Distance).predOf(LessThan<double>(5))));

    ASSERT_FALSE(verify(promise));
}

TEST_F(TestPromise, should_sequential_promise_fail_when_timeout)
{
    prepareEvents({E_SPEED(5), E_SPEED(0), E_DISTANCE(4)});

    auto promise = __seq( __exist(__fact(Stop))
                        , __exist(__fact(Distance).predOf(LessThan<double>(5))));

    ASSERT_FALSE(verify(promise, 2));
}

TEST_F(TestPromise, should_sequential_promise_fail_when_the_last_not_exist_promise_not_success)
{
    prepareEvents({E_SPEED(5), E_SPEED(0), E_COLLISION()});

    auto promise = __seq(__exist(__fact(Stop)), __not_exist(__fact(Collision)));

    ASSERT_FALSE(verify(promise));
}

TEST_F(TestPromise, should_sequential_promise_success_when_the_last_not_exist_promise_success)
{
    prepareEvents({E_SPEED(5), E_SPEED(0), E_NOTHING()});

    auto promise = __seq(__exist(__fact(Stop)), __not_exist(__fact(Collision)));

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_concurrent_promise_success_when_all_exist_promise_success)
{
    prepareEvents({E_SPEED(5), E_SPEED(0), E_COLLISION()});

    auto promise = __con(__exist(__fact(Stop)), __exist(__fact(Collision)));

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_concurrent_promise_fail_when_any_of_exist_promise_fail)
{
    prepareEvents({E_SPEED(1), E_COLLISION()});

    auto promise = __con(__exist(__fact(Stop)), __exist(__fact(Collision)));

    ASSERT_FALSE(verify(promise));
}

TEST_F(TestPromise, should_concurrent_promise_success_when_the_not_exist_promise_success)
{
    prepareEvents({E_SPEED(0), E_NOTHING()});

    auto promise = __con(__exist(__fact(Stop)), __not_exist(__fact(Collision)));

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_optional_promise_success_when_any_promise_success)
{
    prepareEvents({E_SPEED(1), E_COLLISION()});

    auto promise = __opt(__exist(__fact(Stop)), __exist(__fact(Collision)));

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_promise_fail_when_the_daemon_promise_fail)
{
    prepareEvents({E_DISTANCE(5), E_COLLISION()});

    auto promise = __daemon( __not_exist(__fact(Collision))
                           , __exist(__fact(Distance).predOf(LessThan<double>(4))));

    ASSERT_FALSE(verify(promise));
}

TEST_F(TestPromise, should_promise_success_when_the_not_daemon_promise_success)
{
    prepareEvents({E_SPEED(0), E_NOTHING()});

    auto promise = __daemon(__exist(__fact(Collision)), __exist(__fact(Stop)));

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_promise_success_when_the_daemon_promise_be_stopped)
{
    prepareEvents({E_NOTHING(), E_NOTHING()});

    auto promise = __daemon(__not_exist(__fact(Stop)), __not_exist(__fact(Collision)));

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_promise_fix_when_until_promise_fix)
{
    prepareEvents({E_DISTANCE(4), E_DISTANCE(3), E_DISTANCE(2), E_DISTANCE(1)});

    auto promise = __until( __exist(__fact(Duration).predOf(GreaterThan<unsigned int>(2)))
                          , __not_exist(__fact(Distance).predOf(LessThan<double>(2))));

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_promise_success_when_until_promise_terminate)
{
    prepareEvents({E_NOTHING(), E_SPEED(1), E_COLLISION()});

    auto promise = __until(__exist(__fact(Stop)), __exist(__fact(Collision)));

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_optional_promise_fail_when_all_promise_fail)
{
    prepareEvents({E_SPEED(1), E_COLLISION()});

    auto promise = __opt(__exist(__fact(Stop)), __not_exist(__fact(Collision)));

    ASSERT_FALSE(verify(promise));
}

TEST_F(TestPromise, should_composed_promise_success_when_all_promise_success)
{
    prepareEvents({E_DISTANCE(11), E_SPEED(0), E_DISTANCE(9), E_NOTHING(), E_SPEED(1)});

    auto promiseSegment = __con( __not_exist(__fact(Stop))
                               , __exist(__fact(Duration).predOf(GreaterThan<unsigned int>(1))));

    auto promise = __con( __not_exist(__fact(Collision))
                        , __seq( __exist(__fact(Distance).predOf(LessThan<double>(10)))
                               , promiseSegment));

    ASSERT_TRUE(verify(promise));
}

TEST_F(TestPromise, should_listen_the_promise_state)
{
    prepareEvents({E_DISTANCE(11), E_DISTANCE(9), E_DISTANCE(8), E_DISTANCE(5), E_DISTANCE(4)});

    auto promise = __seq( __exist(__fact(Distance).predOf(LessThan<double>(10)))
                        , __exist(__fact(Distance).predOf(EqualTo<int>(5))));

    int EventCount = 0;
    struct EventCountListener : PromiseListener
    {
        EventCountListener(int& count) : count(count){}
    private:
        OVERRIDE(void onEvent(const Event&))
        {
            ++count;
        }
    private:
        int& count;
    }counter(EventCount);

    auto listenedPromise = __listen(counter, promise);

    ASSERT_TRUE(verify(listenedPromise));
    ASSERT_EQ(4, EventCount);
}
