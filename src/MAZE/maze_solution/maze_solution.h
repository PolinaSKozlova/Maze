#ifndef MAZEAPP_MAZE_SOLUTION_H_
#define MAZEAPP_MAZE_SOLUTION_H_

#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <set>

#include "../maze_struct.h"

namespace maze {
class MazeSolution {
 public:
  MazeSolution() = default;
  ~MazeSolution() = default;
  void FindPath(const Coordinate& start, const Coordinate& end);
  std::list<Coordinate> GetPath() const noexcept;
  void SetMaze(std::shared_ptr<maze::MazeInfo> mm);
  std::shared_ptr<maze::MazeInfo> GetMazeData() { return maze_info_; }

 private:
  std::list<Coordinate> CheckNeighbors(const Coordinate cell);
  void BuildPath(std::map<Coordinate, Coordinate>& steps,
                 const Coordinate& start, const Coordinate& end);
  std::list<Coordinate> best_path_;
  std::shared_ptr<maze::MazeInfo> maze_info_;
};

};  // namespace maze

#endif  // MAZEAPP_MAZE_SOLUTION_H_
