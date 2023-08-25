#include <gtest/gtest.h>

#include "../MAZE/maze_creator/maze_ideal.h"

TEST(maze_generator_tests, test_1) {
  maze::MazeCreator creator;
  creator.GenerateMaze(10, 10);
  EXPECT_EQ(10, creator.GetMazeInfo().height);
  EXPECT_EQ(10, creator.GetMazeInfo().width);
}

TEST(maze_generator_tests, test_2) {
  maze::MazeCreator creator;
  creator.GenerateMaze(10, 25);
  EXPECT_EQ(10, creator.GetMazeInfo().height);
  EXPECT_EQ(25, creator.GetMazeInfo().width);
}

TEST(maze_generator_tests, test_3) {
  try {
    maze::MazeCreator creator;
    creator.GenerateMaze(0, 0);
  } catch (std::invalid_argument &e) {
    EXPECT_EQ(std::string(e.what()), "Too small size for maze");
  }
}

TEST(maze_generator_tests, test_4) {
  try {
    maze::MazeCreator creator;
    creator.GenerateMaze(60, 40);
  } catch (std::invalid_argument &e) {
    EXPECT_EQ(std::string(e.what()), "Too big size for maze");
  }
}
