#include <gtest/gtest.h>

#include <vector>

#include "../model/calc_graph.h"

TEST(test, graph_01) {
  s21::CalcGraph graph;
  graph.calcVectorsWithPoints("x+1", -0.1, 0.1);
  std::vector y_values = graph.getVectorY();
  ASSERT_EQ(y_values.size(), 800);
}
