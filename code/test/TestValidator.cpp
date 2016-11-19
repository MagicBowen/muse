#include <gtest/gtest.h>
#include <muse/event/EventQueue.h>
#include <muse/event/Event.h>
#include <muse/fact/CollisionFact.h>
#include <muse/validator/ExistValidator.h>
#include <muse/base/Role.h>
#include <muse/simulation/Simulation.h>

USING_MUSE_NS;

struct TestValidator : testing::Test
{
};

TEST_F(TestValidator, should_exist_when_fact_is_occurred)
{
    EventQueue::getInstance().push(Event{COLLISION, 0});

    CollisionFact fact;
    ExistValidator validator(fact);

    Simulation simulation(validator);
    simulation.play();

    ASSERT_TRUE(simulation.isSuccess());
}
