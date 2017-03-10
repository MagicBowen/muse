#include <gtest/gtest.h>
#include <fakefact/include/event/EventGenerator.h>
#include <fakefact/include/runner/PromiseRunner.h>
#include <fakefact/include/event/FakeEvent.h>
#include <outdsl/include/PromiseFactory.h>


USING_MUSE_NS;

struct TestOutDsl : testing::Test
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

TEST_F(TestOutDsl, should_create_exist_promise_with_simple_fact)
{
    prepareEvents({E_DISTANCE(10), E_DISTANCE(9), E_DISTANCE(8)});

    const char* json = R"({ "type" : "exist", "fact" : { "name" : "distance", "pred" : {"name" : "equalto", "param" : 9}}})";

    Promise* promise = PromiseFactory::create(json);

    ASSERT_NE(nullptr, promise);
    ASSERT_TRUE(verify(*promise));
}

TEST_F(TestOutDsl, should_create_not_exist_promise_with_simple_fact)
{
    prepareEvents({E_NOTHING(), E_COLLISION(), E_NOTHING()});

    const char* json = R"({ "type" : "notexist", "fact" : { "name" : "collision"}})";


    Promise* promise = PromiseFactory::create(json);

    ASSERT_NE(nullptr, promise);
    ASSERT_FALSE(verify(*promise));
}

TEST_F(TestOutDsl, should_create_closure_fact_with_average_algo_and_between_pred)
{
    prepareEvents({E_DISTANCE(1), E_DISTANCE(2), E_DISTANCE(3.5), E_DISTANCE(4)});

    const char* json = R"({ "type" : "exist", 
                            "fact" : { "name" : "distanceto",
                                       "param": 1,
                                       "closure" : true,
                                       "algo" : "average",
                                       "pred" : {"name" : "between", "param" : [2.0, 3.5]}
                                     }
                          })";


    Promise* promise = PromiseFactory::create(json);

    ASSERT_NE(nullptr, promise);
    ASSERT_TRUE(verify(*promise));
}

TEST_F(TestOutDsl, should_composed_promise_success_when_all_promise_success)
{
    prepareEvents({E_DISTANCE(11), E_SPEED(0), E_DISTANCE(9), E_NOTHING(), E_SPEED(1)});

    const char* json = R"(
        {
            "type" : "concurrent",     
            "promises" : [ {"type" : "notexist", "fact" : {"name" : "collision"}},
                           {"type" : "sequential", "promises" : [ {"type" : "exist", "fact" : {"name" : "distance", "pred" : {"name" : "lessthan", "param" : 10}}},
                                                                  {"type" : "concurrent", "promises" : [ {"type" : "notexist", "fact" : {"name" : "stop"}},
                                                                                                         {"type" : "exist", "fact" : {"name" : "duration", "pred" : {"name" : "greaterthan", "param" : 1}}}
                                                                                                       ]}
                                                                ]}
                         ]
        }
    )";

    Promise* promise = PromiseFactory::create(json);

    ASSERT_NE(nullptr, promise);
    ASSERT_TRUE(verify(*promise));
}

