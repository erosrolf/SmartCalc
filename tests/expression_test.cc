#include "../model/expression.h"

#include <gtest/gtest.h>

TEST(constuct_without_x, overflow_expression) {
  s21::Expression expression_256size(
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "1111111111111111111111111111111111111111");
  ASSERT_FALSE(expression_256size.is_valid);
}

TEST(constuct_without_x, expression_maxsize255) {
  s21::Expression expression(
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "111111111111111111111111111111111111111");
  ASSERT_TRUE(expression.data.size() == 255);
  ASSERT_TRUE(expression.is_valid);
}

TEST(constuct_without_x, expression_empty) {
  s21::Expression exp("");
  ASSERT_FALSE(exp.is_valid);
}

TEST(constuct_with_x, valid_expression_01) {
  s21::Expression exp("xxxxxxxxxx", "01");
  ASSERT_TRUE(exp.is_valid);
}

TEST(constuct_with_x, valid_expression_02) {
  s21::Expression exp("xxxxxxxxxx");
  ASSERT_TRUE(exp.is_valid);
}

TEST(constuct_with_x, valid_expression_03) {
  s21::Expression exp("x", "xxx");
  ASSERT_TRUE(exp.is_valid);
  ASSERT_TRUE(exp.data.size() == 3);
}

TEST(constuct_with_x, invalid_expression_01) {
  s21::Expression exp("xxxxxxxxxxXXXXXXXXXXxxxxxx", "1234567890");
  ASSERT_FALSE(exp.is_valid);
}

TEST(expression_correcter, to_lower_case) {
  s21::Expression exp("HelloWORLD");
  ASSERT_EQ(exp.data, "helloworld");
}

TEST(expression_correcter, without_spaces) {
  s21::Expression exp("   Hello  WORLD   ");
  ASSERT_EQ(exp.data, "helloworld");
}

TEST(expression_correcter, to_dots) {
  s21::Expression exp("1,234");
  ASSERT_EQ(exp.data, "1.234");
}
