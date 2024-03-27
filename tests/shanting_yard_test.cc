#include "../model/shanting_yard.h"

#include <gtest/gtest.h>

#include <list>
#include <string>

#include "../model/lexems.h"

TEST(shanting_yard_test, construct_01) {
  std::list<std::string> ref;
  ref.push_back("1");
  ref.push_back("-");
  ref.push_back("sin");
  s21::ShantingYard polish("sin-1");
  std::list<s21::Lexem> lexems = polish.data();
  auto ref_it = ref.cbegin();
  for (auto it : polish.data()) {
    EXPECT_EQ(it.str, *ref_it);
    ++ref_it;
  }
}

TEST(shanting_yard_test, construct_02) {
  std::list<std::string> ref;
  ref.push_back("111");
  ref.push_back("sqrt");
  ref.push_back("1");
  ref.push_back("2");
  ref.push_back("/");
  ref.push_back("111");
  ref.push_back("2");
  ref.push_back("^");
  ref.push_back("2");
  ref.push_back("-");
  ref.push_back("sin");
  ref.push_back("*");
  ref.push_back("-");
  s21::ShantingYard polish("sqrt(111)-1/2*sin(111^2-2)");
  auto ref_it = ref.cbegin();
  for (auto it : polish.data()) {
    EXPECT_EQ(it.str, *ref_it);
    ++ref_it;
  }
}

TEST(shanting_yard_test, construct_03) {
  s21::ShantingYard polish(")");
  ASSERT_EQ(polish.isValid(), false);
}

TEST(shanting_yard_test, construct_04) {
  s21::ShantingYard polish("x+x");
  std::list<std::string> ref;
  ref.push_back("0");
  ref.push_back("0");
  ref.push_back("+");
  auto ref_it = ref.cbegin();
  for (auto it : polish.data()) {
    EXPECT_EQ(it.str, *ref_it);
    ++ref_it;
  }
}

TEST(shanting_yard_test, construct_05) {
  s21::ShantingYard polish("x+x", "22");
  std::list<std::string> ref;
  ref.push_back("22");
  ref.push_back("22");
  ref.push_back("+");
  auto ref_it = ref.cbegin();
  for (auto it : polish.data()) {
    EXPECT_EQ(it.str, *ref_it);
    ++ref_it;
  }
}

TEST(shanting_yard_test, construct_06) {
  s21::ShantingYard polish("x", "22+22");
  std::list<std::string> ref;
  ref.push_back("22");
  ref.push_back("22");
  ref.push_back("+");
  auto ref_it = ref.cbegin();
  for (auto it : polish.data()) {
    EXPECT_EQ(it.str, *ref_it);
    ++ref_it;
  }
}

TEST(shanting_yard_test, construct_07) {
  s21::ShantingYard polish(")2+2(");
  ASSERT_EQ(polish.isValid(), false);
}

TEST(shanting_yard_test, construct_08) {
  s21::ShantingYard polish("2+.");
  ASSERT_EQ(polish.isValid(), false);
}

TEST(shanting_yard_test, getExpressionString) {
  std::string ref = "sqrt(111)-1/2*sin(111^2-2)";
  s21::ShantingYard polish("sqrt(111)-1/2*sin(111^2-2)");
  EXPECT_EQ(ref, polish.getExpressionString());
}

TEST(shanting_yard_test, getReversePolishString) {
  std::string ref = "- * sin - 2 ^ 2 111 / 2 1 sqrt 111";
  s21::ShantingYard polish("sqrt(111)-1/2*sin(111^2-2)");
  EXPECT_EQ(ref, polish.getReversePolishString());
}
