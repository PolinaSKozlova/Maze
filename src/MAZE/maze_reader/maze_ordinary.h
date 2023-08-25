#ifndef MAZEAPP_MAZE_ORDINARY_H_
#define MAZEAPP_MAZE_ORDINARY_H_

#include <iostream>
#include <utility>
#include <vector>

#include "../maze_struct.h"

namespace maze {
class MazeReader {
 public:
  MazeReader() = default;
  void GenerateMaze(const std::string& filepath);
  ~MazeReader() = default;
  void ParseFile();
  std::pair<std::vector<std::vector<bool>>, std::vector<std::vector<bool>>>
  GetWalls() const;
  std::pair<size_t, size_t> GetSize() const;
  MazeInfo GetData() const;

 private:
  void ReadSize(const std::string& line);
  void CheckSize() const;
  std::vector<bool> ReadWalls(const std::string& line);
  bool CheckNumberBool(int sym) const noexcept;
  MazeInfo data_;
};
}  // namespace maze

#endif  // MAZEAPP_MAZE_ORDINARY_H_
