#include "../model/polish_calc.h"

#include <gtest/gtest.h>

#include "../model/shanting_yard.h"

TEST(polish_calc, calc_01) {
  s21::PolishCalc calc;
  calc.calculate("2+2");
  ASSERT_EQ(calc.result(), 4);
}

TEST(polish_calc, calc_02) {
  s21::PolishCalc calc;
  calc.calculate("sin2");
  EXPECT_NEAR(calc.result(), 0.909297467, 9e-7);
}

TEST(polish_calc, calc_03) {
  s21::PolishCalc calc;
  calc.calculate("2^3^2");
  ASSERT_EQ(calc.result(), 512);
}

TEST(polish_calc, calc_04) {
  s21::PolishCalc calc;
  calc.calculate("2*e");
  EXPECT_NEAR(calc.result(), 5.43656365692, 9e-7);
}

TEST(polish_calc, calc_05) {
  s21::PolishCalc calc;
  calc.calculate("1e-2 * 5");
  ASSERT_EQ(calc.result(), 0.05);
}

TEST(polish_calc, calc_06) {
  s21::PolishCalc calc;
  calc.calculate("2+");
  ASSERT_EQ(calc.result(), 0);
  ASSERT_EQ(calc.status(), s21::Status::kInvalidExpression);
}

TEST(polish_calc, calc_07) {
  s21::PolishCalc calc;
  calc.calculate("1234567890");
  ASSERT_EQ(calc.result(), 1234567890);
  ASSERT_EQ(calc.status(), s21::Status::kOk);
}

TEST(polish_calc, calc_08) {
  s21::PolishCalc calc;
  calc.calculate("c");
  ASSERT_EQ(calc.result(), 0);
  ASSERT_EQ(calc.status(), s21::Status::kInvalidExpression);
}

TEST(polish_calc, calc_09) {
  s21::PolishCalc calc;
  calc.calculate("1.2*(-1)");
  ASSERT_EQ(calc.status(), s21::Status::kOk);
  ASSERT_EQ(calc.result(), -1.2);
}

TEST(polish_calc, calc_10) {
  s21::PolishCalc calc;
  calc.calculate("-1cos2");
  ASSERT_EQ(calc.status(), s21::Status::kOk);
  EXPECT_NEAR(calc.result(), 0.41614683654, 9e-7);
}

TEST(polish_calc, calc_11) {
  s21::PolishCalc calc;
  calc.calculate("xx", "5");
  ASSERT_EQ(calc.status(), s21::Status::kOk);
  ASSERT_EQ(calc.result(), 25);
}

TEST(polish_calc, calc_12) {
  s21::PolishCalc calc;
  calc.calculate("tanx", "5");
  ASSERT_EQ(calc.status(), s21::Status::kOk);
  EXPECT_NEAR(calc.result(), -3.38051500625, 9e-7);
}

TEST(polish_calc, calc_13) {
  s21::PolishCalc calc;
  calc.calculate("asinx", "-0.123");
  ASSERT_EQ(calc.status(), s21::Status::kOk);
  EXPECT_NEAR(calc.result(), -0.1233123, 9e-7);
}

TEST(polish_calc, calc_14) {
  s21::PolishCalc calc;
  calc.calculate("x", "acos-0.123");
  ASSERT_EQ(calc.status(), s21::Status::kOk);
  EXPECT_NEAR(calc.result(), 1.694109, 9e-7);
}

TEST(polish_calc, calc_15) {
  s21::PolishCalc calc;
  calc.calculate("sqrt9sqrt5");
  ASSERT_EQ(calc.status(), s21::Status::kOk);
  EXPECT_NEAR(calc.result(), 6.7082039325, 9e-7);
}

TEST(polish_calc, calc_16) {
  s21::PolishCalc calc;
  calc.calculate("sin1cos2tan1ln3log10");
  ASSERT_EQ(calc.status(), s21::Status::kOk);
  EXPECT_NEAR(calc.result(), -0.59914580104, 9e-7);
}

TEST(polish_calc, calc_17) {
  s21::PolishCalc calc;
  calc.calculate("125%x", "15");
  ASSERT_EQ(calc.status(), s21::Status::kOk);
  ASSERT_EQ(calc.result(), 5);
}

TEST(polish_calc, calc_18) {
  s21::PolishCalc calc;
  calc.calculate("125x5", "%");
  ASSERT_EQ(calc.status(), s21::Status::kInvalidExpression);
  ASSERT_EQ(calc.result(), 0);
}

TEST(polish_calc, calc_19) {
  s21::PolishCalc calc;
  calc.calculate("-sin");
  ASSERT_EQ(calc.status(), s21::Status::kInvalidExpression);
  ASSERT_EQ(calc.result(), 0);
}

TEST(polish_calc, calc_20) {
  s21::PolishCalc calc;
  calc.calculate("(3-1)/2");
  ASSERT_EQ(calc.status(), s21::Status::kOk);
  ASSERT_EQ(calc.result(), 1);
}

TEST(polish_calc, calc_21) {
  s21::PolishCalc calc;
  calc.calculate("atan10");
  ASSERT_EQ(calc.status(), s21::Status::kOk);
  EXPECT_NEAR(calc.result(), 1.47112767, 9e-7);
}

TEST(polish_calc, calc_22) {
  s21::PolishCalc calc;
  calc.calculate("(e)(e)");
  ASSERT_EQ(calc.status(), s21::Status::kOk);
  EXPECT_NEAR(calc.result(), 7.38905609893, 9e-7);
}
