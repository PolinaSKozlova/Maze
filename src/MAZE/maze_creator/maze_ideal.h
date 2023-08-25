#ifndef MAZEAPP_MAZE_IDEAL_H_
#define MAZEAPP_MAZE_IDEAL_H_

#include <iostream>
#include <vector>

#include "../maze_struct.h"

namespace maze {
class MazeCreator {
 public:
  MazeCreator() = default;
  ~MazeCreator() = default;
  void GenerateMaze(int height, int width);
  void SaveMaze(const std::string &filepath) const;
  MazeInfo GetMazeInfo() const noexcept;
  void SetMazeInfo(const MazeInfo &other) { maze_info_ = other; }

 private:
  void StartDrawingMaze();
  void MemoryAllocateForWalls(std::vector<std::vector<bool>> &walls);
  void FillMazeMatrix() noexcept;
  void SetUniqueSetValues(int &counter) noexcept;
  void PrepareNewLine(const int row) noexcept;
  void BuildVerticalWalls(const int row) noexcept;
  void BuildHorizontalWalls(const int row) noexcept;
  void CheckHorizontalWalls(const int row) noexcept;
  void CheckSize(size_t rows, size_t cols) const;
  void BuildLastWall() noexcept;
  int CalculateHorizontalWalls(const int row, const int value) const;
  bool GenerateRandomBool();
  void MergeEqualSet(const int index);
  std::vector<int> unique_sets;
  MazeInfo maze_info_;
};

};  // namespace maze

#endif  // MAZEAPP_MAZE_IDEAL_H_
