#include <gtest/gtest.h>

#include "../MAZE/maze_reader/maze_ordinary.h"
#include "../MAZE/maze_solution/maze_solution.h"

TEST(maze_solution_test, test_1) {
  maze::MazeReader reader;
  maze::MazeSolution solution;
  reader.GenerateMaze("maze_examples/example10x10");
  solution.SetMaze(std::make_shared<maze::MazeInfo>(reader.GetData()));
  maze::Coordinate start(1, 1);
  maze::Coordinate end(7, 7);
  solution.FindPath(start, end);
  std::list<maze::Coordinate> result_path{
      maze::Coordinate(1, 1), maze::Coordinate(0, 1), maze::Coordinate(0, 0),
      maze::Coordinate(1, 0), maze::Coordinate(2, 0), maze::Coordinate(2, 1),
      maze::Coordinate(2, 2), maze::Coordinate(1, 2), maze::Coordinate(1, 3),
      maze::Coordinate(2, 3), maze::Coordinate(3, 3), maze::Coordinate(3, 4),
      maze::Coordinate(4, 4), maze::Coordinate(4, 3), maze::Coordinate(5, 3),
      maze::Coordinate(5, 2), maze::Coordinate(4, 2), maze::Coordinate(3, 2),
      maze::Coordinate(3, 1), maze::Coordinate(3, 0), maze::Coordinate(4, 0),
      maze::Coordinate(4, 1), maze::Coordinate(5, 1), maze::Coordinate(6, 1),
      maze::Coordinate(7, 1), maze::Coordinate(7, 2), maze::Coordinate(7, 3),
      maze::Coordinate(8, 3), maze::Coordinate(8, 2), maze::Coordinate(8, 1),
      maze::Coordinate(8, 0), maze::Coordinate(9, 0), maze::Coordinate(9, 1),
      maze::Coordinate(9, 2), maze::Coordinate(9, 3), maze::Coordinate(9, 4),
      maze::Coordinate(9, 5), maze::Coordinate(9, 6), maze::Coordinate(8, 6),
      maze::Coordinate(8, 5), maze::Coordinate(7, 5), maze::Coordinate(7, 6),
      maze::Coordinate(7, 7)};
  std::list<maze::Coordinate> solution_path = solution.GetPath();
  EXPECT_EQ(result_path.size(), solution_path.size());
  auto res_it = result_path.begin();
  auto sol_it = solution_path.begin();
  for (; res_it != result_path.end() && sol_it != solution_path.end();
       ++res_it, ++sol_it) {
    EXPECT_EQ(res_it->GetXY(), sol_it->GetXY());
  }
}

TEST(maze_solution_test, test_2) {
  maze::MazeReader reader;
  maze::MazeSolution solution;
  reader.GenerateMaze("maze_examples/example3x3");
  solution.SetMaze(std::make_shared<maze::MazeInfo>(reader.GetData()));
  maze::Coordinate start(0, 1);
  maze::Coordinate end(2, 0);
  solution.FindPath(start, end);
  std::list<maze::Coordinate> result_path{
      maze::Coordinate(0, 1), maze::Coordinate(0, 0), maze::Coordinate(1, 0),
      maze::Coordinate(2, 0)};
  std::list<maze::Coordinate> solution_path = solution.GetPath();
  EXPECT_EQ(result_path.size(), solution_path.size());
  auto res_it = result_path.begin();
  auto sol_it = solution_path.begin();
  for (; res_it != result_path.end() && sol_it != solution_path.end();
       ++res_it, ++sol_it) {
    EXPECT_EQ(res_it->GetXY(), sol_it->GetXY());
  }
}

TEST(maze_solution_test, test_3) {
  maze::MazeReader reader;
  maze::MazeSolution solution;

  reader.GenerateMaze("maze_examples/loop_maze5x8");

  solution.SetMaze(std::make_shared<maze::MazeInfo>(reader.GetData()));
  maze::Coordinate start(0, 1);
  maze::Coordinate end(2, 0);
  solution.FindPath(start, end);
  std::list<maze::Coordinate> result_path{
      maze::Coordinate(0, 1), maze::Coordinate(0, 2), maze::Coordinate(0, 3),
      maze::Coordinate(0, 4), maze::Coordinate(1, 4), maze::Coordinate(1, 3),
      maze::Coordinate(2, 3), maze::Coordinate(2, 2), maze::Coordinate(2, 1),
      maze::Coordinate(2, 0)};
  std::list<maze::Coordinate> solution_path = solution.GetPath();
  EXPECT_EQ(result_path.size(), solution_path.size());
  auto res_it = result_path.begin();
  auto sol_it = solution_path.begin();
  for (; res_it != result_path.end() && sol_it != solution_path.end();
       ++res_it, ++sol_it) {
    EXPECT_EQ(res_it->GetXY(), sol_it->GetXY());
  }
}

TEST(maze_solution_test, test_4) {
  maze::MazeReader reader;
  maze::MazeSolution solution;
  reader.GenerateMaze("maze_examples/not_ideal_maze5x8");
  try {
    solution.SetMaze(std::make_shared<maze::MazeInfo>(reader.GetData()));
    maze::Coordinate start(0, 0);
    maze::Coordinate end(4, 7);
    solution.FindPath(start, end);
  } catch (std::invalid_argument &e) {
    std::list<maze::Coordinate> solution_path = solution.GetPath();
    EXPECT_EQ(0, solution_path.size());
    EXPECT_EQ(std::string(e.what()), "Path doesn't find");
  }
}

TEST(maze_solution_test, test_5) {
  maze::MazeReader reader;
  maze::MazeSolution solution;
  reader.GenerateMaze("maze_examples/loop_maze5x8");
  try {
    solution.SetMaze(std::make_shared<maze::MazeInfo>(reader.GetData()));
    maze::Coordinate start(0, 0);
    maze::Coordinate end(4, 7);
    solution.FindPath(start, end);
  } catch (std::invalid_argument &e) {
    std::list<maze::Coordinate> solution_path = solution.GetPath();
    EXPECT_EQ(0, solution_path.size());
    EXPECT_EQ(std::string(e.what()), "Path doesn't find");
  }
}
