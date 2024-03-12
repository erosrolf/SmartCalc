#include <gtest/gtest.h>

#include "../model/lexems.h"

TEST(lexems_test, constructor_with_invalid_params_01) {
  s21::Lexems lex("");
  EXPECT_FALSE(lex.isValid());
}

TEST(lexems_test, constructor_with_invalid_params_02) {
  std::string count256 =
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "1111111111111111111111111111111111111111";
  s21::Lexems lex(count256);
  EXPECT_FALSE(lex.isValid());
}

TEST(lexems_test, constructor_with_invalid_params_03) {
  s21::Lexems lex("Hello world!");
  EXPECT_FALSE(lex.isValid());
}

TEST(lexems_test, constructor_with_invalid_params_04) {
  s21::Lexems lex(" ");
  EXPECT_FALSE(lex.isValid());
}

TEST(lexems_test, constructor_with_invalid_params_05) {
  s21::Lexems lex("\n");
  EXPECT_FALSE(lex.isValid());
}

TEST(lexems_test, constructor_with_invalid_params_06) {
  s21::Lexems lex("");
  EXPECT_FALSE(lex.isValid());
}

TEST(lexems_test, constructor_with_invalid_params_07) {
  s21::Lexems lex("son1");
  EXPECT_FALSE(lex.isValid());
}

TEST(lexems_test, constructor_with_invalid_params_08) {
  s21::Lexems lex("c");
  EXPECT_FALSE(lex.isValid());
}

TEST(lexems_test, constructor_with_invalid_params_09) {
  s21::Lexems lex("-");
  EXPECT_FALSE(lex.isValid());
}

TEST(lexems_test, constructor_with_valid_params_01) {
  std::string count255 =
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "111111111111111111111111111111111111111";
  s21::Lexems lex(count255);
  EXPECT_TRUE(lex.isValid());
}

TEST(lexems_test, constructor_with_valid_params_02) {
  std::string input("2.253+1+5e-6-5");
  s21::Lexems lex(input);
  EXPECT_TRUE(lex.isValid());
  EXPECT_EQ(lex.size(), 7);
}

TEST(lexems_test, constructor_with_valid_params_03) {
  std::string input("2.253+1+e-6-5");
  s21::Lexems lex(input);
  EXPECT_TRUE(lex.isValid());
  EXPECT_EQ(lex.size(), 9);
}

TEST(lexems_test, constructor_with_valid_params_04) {
  std::string exponential("7.8900e-5");
  s21::Lexems lex(exponential);
  EXPECT_EQ(lex.data().front().str, exponential);
}

TEST(lexems_test, constructor_with_valid_params_05) {
  s21::Lexems lex("2+e+5");
  EXPECT_TRUE(lex.isValid());
}

TEST(lexems_test, constructor_with_valid_params_06) {
  s21::Lexems lex("2*5");
  EXPECT_TRUE(lex.isValid());
}

TEST(lexems_test, constructor_with_valid_params_07) {
  s21::Lexems lex("5");
  EXPECT_TRUE(lex.isValid());
}

TEST(lexems_test, constructor_with_valid_params_08) {
  s21::Lexems lex("1.2*(-1.2)");
  EXPECT_TRUE(lex.isValid());
}

TEST(lexems_test, constructor_with_valid_params_09) {
  s21::Lexems lex("1.2*(+1.2)");
  EXPECT_TRUE(lex.isValid());
}

TEST(lexems_test, constructor_with_valid_params_10) {
  s21::Lexems lex("(e)(e)");
  EXPECT_TRUE(lex.isValid());
  lex.printAllLexems();
}

TEST(lexems_test, bracketsIsCorrect_01) {
  s21::Lexems lex("2+()");
  EXPECT_FALSE(lex.isValid());
}

TEST(lexems_test, bracketsIsCorrect_02) {
  s21::Lexems lex("(2+(1)");
  EXPECT_FALSE(lex.isValid());
}

TEST(lexems_test, bracketsIsCorrect_03) {
  s21::Lexems lex("(2+(1)))(");
  EXPECT_FALSE(lex.isValid());
}

TEST(lexems_test, add_multiplication_01) {
  s21::Lexems lex("sinecose");
  EXPECT_TRUE(lex.isValid());
  EXPECT_EQ(lex.size(), 5);
}

TEST(lexems_test, add_multiplication_02) {
  s21::Lexems lex("(2)(2)");
  EXPECT_TRUE(lex.isValid());
  EXPECT_EQ(lex.size(), 7);
}

TEST(lexems_test, add_multiplication_03) {
  s21::Lexems lex("(1)cose");
  EXPECT_TRUE(lex.isValid());
  EXPECT_EQ(lex.size(), 6);
}

TEST(lexems_test, add_multiplication_04) {
  s21::Lexems lex("-1cose");
  EXPECT_TRUE(lex.isValid());
  EXPECT_EQ(lex.size(), 5);
}

TEST(lexems_test, add_multiplication_05) {
  s21::Lexems lex("5(2)");
  EXPECT_TRUE(lex.isValid());
  EXPECT_EQ(lex.size(), 5);
}
TEST(lexems_test, add_multiplication_06) {
  s21::Lexems lex("(e)(e)");
  EXPECT_TRUE(lex.isValid());
  EXPECT_EQ(lex.size(), 7);
}
