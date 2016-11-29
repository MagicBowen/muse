#include <gtest/gtest.h>
#include <muse/pred/Between.h>
#include <muse/pred/Variance.h>
#include <muse/pred/Compose.h>
#include <muse/pred/NotPred.h>
#include <iostream>

USING_MUSE_NS;

TEST(TestPred, should_middle_number_between_in_bounds)
{
    ASSERT_TRUE(Between<int>(1, 3)(2));
}

TEST(TestPred, should_out_of_range_number_not_between_in_bounds)
{
    ASSERT_FALSE(Between<int>(1, 3)(3));
}

TEST(TestPred, should_not_pred_return_the_negative_result)
{
    ASSERT_TRUE(__not_pred(Between<int>(1, 3))(3));
}

TEST(TestPred, should_get_average_one_by_one)
{
    Average<int, int> average;

    ASSERT_EQ(3, average(3));
    ASSERT_EQ(4, average(5));
    ASSERT_EQ(6, average(10));
}

TEST(TestPred, should_get_variance_one_by_one)
{
    Variance<int, double> variance;

    ASSERT_NEAR(0.00, variance(3), 0.01);
    ASSERT_NEAR(1.41, variance(5), 0.01);
    ASSERT_NEAR(2.00, variance(1), 0.01);
}

TEST(TestPred, should_compose_variance_and_pred)
{
    auto pred = __pred_of(Variance<int, double>(), LessThan<double>(3));

    ASSERT_TRUE(pred(3));
    ASSERT_TRUE(pred(5));
    ASSERT_TRUE(pred(1));
}

TEST(TestPred, should_compose_variance_and_not_pred)
{
    auto pred = __pred_of(Variance<int, double>(), __not_pred(LessThan<double>(3)));

    ASSERT_FALSE(pred(3));
    ASSERT_FALSE(pred(5));
    ASSERT_FALSE(pred(1));

    std::cout << pred.info() << std::endl;
}
