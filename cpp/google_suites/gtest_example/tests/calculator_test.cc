#include <gtest/gtest.h>

#include <tuple>
#include <vector>

#include "calculator.h"

class CalculatorTest : public ::testing::Test {
 protected:
  Calculator calc_;
};

TEST_F(CalculatorTest, BasicArithmetic) {
  EXPECT_EQ(calc_.Add(2, 3), 5);
  EXPECT_EQ(calc_.Sub(7, 4), 3);
  EXPECT_EQ(calc_.Mul(6, 7), 42);
}

TEST_F(CalculatorTest, Division) { EXPECT_DOUBLE_EQ(calc_.Div(8.0, 2.0), 4.0); }

TEST_F(CalculatorTest, Factorial) {
  EXPECT_EQ(calc_.Factorial(0), 1u);
  EXPECT_EQ(calc_.Factorial(5), 120u);
}

TEST_F(CalculatorTest, SumVector) {
  std::vector<int> v{1, 2, 3, 4, 5};
  EXPECT_EQ(calc_.SumVector(v), 15);
}

TEST_F(CalculatorTest, EvenOdd) {
  EXPECT_TRUE(calc_.IsEven(10));
  EXPECT_FALSE(calc_.IsEven(11));
}

TEST_F(CalculatorTest, PrimeCheck) {
  EXPECT_TRUE(calc_.IsPrime(97));
  EXPECT_FALSE(calc_.IsPrime(1));
  EXPECT_FALSE(calc_.IsPrime(100));
}

class AddParamTest
    : public ::testing::TestWithParam<std::tuple<int, int, int>> {};

TEST_P(AddParamTest, AddPairs) {
  Calculator c;
  auto [a, b, expected] = GetParam();
  EXPECT_EQ(c.Add(a, b), expected);
}

INSTANTIATE_TEST_SUITE_P(
    AddParamSuite, AddParamTest,
    ::testing::Values(std::make_tuple(0, 0, 0), std::make_tuple(1, 2, 3),
                      std::make_tuple(-5, 5, 0),
                      std::make_tuple(123, 456, 579),
                      std::make_tuple(-10, -20, -30)));

TEST_F(CalculatorTest, SqrtPositive) { EXPECT_DOUBLE_EQ(calc_.Sqrt(16.0), 4.0); }

TEST_F(CalculatorTest, RepeatString) {
  EXPECT_EQ(calc_.Repeat("ab", 3), "ababab");
}

TEST(CalculatorDeathTest, DivisionByZeroDies) {
  Calculator c;
  EXPECT_DEATH(c.Div(1.0, 0.0), "");
}

TEST(CalculatorDeathTest, NegativeSqrtDies) {
  Calculator c;
  EXPECT_DEATH(c.Sqrt(-1.0), "");
}

TEST(CalculatorDeathTest, RepeatNegativeDies) {
  Calculator c;
  EXPECT_DEATH(c.Repeat("x", -1), "");
}
