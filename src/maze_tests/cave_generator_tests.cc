#include <gtest/gtest.h>

#include "../MAZE/cave_generator/cave.h"
#include "../MAZE/cave_generator/cave_generator.h"

TEST(cave_generator_tests, test_1) {
  CaveGenerator cg;
  cg.Generate(10, 10, 5, {3, 4});
  EXPECT_EQ(10, cg.GetCave().Rows());
  EXPECT_EQ(10, cg.GetCave().Cols());
}

TEST(cave_generator_tests, test_2) {
  CaveGenerator cg;
  cg.Generate("maze_examples/cave10x10", {3, 4});
  int i = 0;
  while (i++ < 100) {
    cg.NextIter();
  }
  Cave res(1, 1);
  res.ParseCaveFile("maze_examples/cave_result_10");
  for (int j = 0; j < res.Rows() * res.Cols(); ++j) {
    EXPECT_EQ(res.GetCells()[j], cg.GetCave().GetCells()[j]);
  }
}

TEST(cave_generator_tests, test_3) {
  CaveGenerator cg;
  cg.Generate("maze_examples/cave50x50", {5, 2});
  int i = 0;
  while (i++ < 100) {
    cg.NextIter();
  }
  Cave res(1, 1);
  res.ParseCaveFile("maze_examples/cave_result_50");
  for (int j = 0; j < res.Rows() * res.Cols(); ++j) {
    EXPECT_EQ(res.GetCells()[j], cg.GetCave().GetCells()[j]);
  }
}
