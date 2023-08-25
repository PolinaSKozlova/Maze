#include "maze_ideal.h"

#include <fstream>
#include <random>
#include <sstream>

namespace maze {
void MazeCreator::GenerateMaze(int height, int width) {
  CheckSize(height, width);
  maze_info_.height = height;
  maze_info_.width = width;
  StartDrawingMaze();
}

void MazeCreator::CheckSize(size_t rows, size_t cols) const {
  if (rows < 1 || cols < 1)
    throw std::invalid_argument("Too small size for maze");
  if (rows > 50 || cols > 50)
    throw std::invalid_argument("Too big size for maze");
}

void MazeCreator::SaveMaze(const std::string& filepath) const {
  std::ofstream file_for_save;
  file_for_save.open(filepath);
  if (!file_for_save.is_open()) throw std::invalid_argument("Can't open file");
  file_for_save << maze_info_.height << " " << maze_info_.width << std::endl;
  for (size_t i = 0; i < maze_info_.height; ++i) {
    for (size_t j = 0; j < maze_info_.width; ++j) {
      if (j == maze_info_.width - 1) {
        file_for_save << maze_info_.v_walls[i][j];
      } else {
        file_for_save << maze_info_.v_walls[i][j] << " ";
      }
    }
    file_for_save << std::endl;
  }

  for (size_t i = 0; i < maze_info_.height; ++i) {
    file_for_save << std::endl;
    for (size_t j = 0; j < maze_info_.width; ++j) {
      if (j == maze_info_.width - 1) {
        file_for_save << maze_info_.h_walls[i][j];
      } else {
        file_for_save << maze_info_.h_walls[i][j] << " ";
      }
    }
  }

  file_for_save.close();
}

MazeInfo MazeCreator::GetMazeInfo() const noexcept { return maze_info_; }

void MazeCreator::StartDrawingMaze() {
  MemoryAllocateForWalls(maze_info_.v_walls);
  MemoryAllocateForWalls(maze_info_.h_walls);
  FillMazeMatrix();
}

void MazeCreator::MemoryAllocateForWalls(
    std::vector<std::vector<bool>>& walls) {
  walls.clear();
  walls.resize(maze_info_.height);
  for (size_t i = 0; i < maze_info_.height; ++i) {
    walls[i].resize(maze_info_.width);
  }
}

void MazeCreator::FillMazeMatrix() noexcept {
  unique_sets.clear();
  unique_sets.resize(maze_info_.width);
  int counter = 0;
  for (size_t index = 0; index < maze_info_.height; ++index) {
    SetUniqueSetValues(counter);
    BuildVerticalWalls(index);
    if (index < maze_info_.height - 1) {
      BuildHorizontalWalls(index);
      CheckHorizontalWalls(index);
      PrepareNewLine(index);
    }
  }
  BuildLastWall();
}

void MazeCreator::SetUniqueSetValues(int& counter) noexcept {
  for (int& set : unique_sets) {
    if (set == 0) {
      set = ++counter;
    }
  }
}

void MazeCreator::BuildVerticalWalls(const int row) noexcept {
  for (size_t i = 0; i < unique_sets.size() - 1; ++i) {
    if (unique_sets[i] != unique_sets[i + 1]) {
      if (GenerateRandomBool()) {
        maze_info_.v_walls[row][i] = true;
      } else {
        MergeEqualSet(i);
      }
    } else {
      maze_info_.v_walls[row][i] = true;
    }
  }
  maze_info_.v_walls[row][unique_sets.size() - 1] = true;
}

void MazeCreator::BuildHorizontalWalls(const int row) noexcept {
  for (size_t i = 0; i < unique_sets.size(); ++i) {
    if (GenerateRandomBool()) {
      maze_info_.h_walls[row][i] = true;
    }
  }
}

void MazeCreator::BuildLastWall() noexcept {
  for (size_t i = 0; i < unique_sets.size(); ++i) {
    maze_info_.h_walls[maze_info_.height - 1][i] = true;
    if (unique_sets[i] != unique_sets[i + 1]) {
      maze_info_.v_walls[maze_info_.height - 1][i] = false;
      MergeEqualSet(i);
    }
  }
  maze_info_.v_walls[maze_info_.height - 1][maze_info_.width - 1] = true;
  maze_info_.h_walls[maze_info_.height - 1][maze_info_.width - 1] = true;
}

void MazeCreator::PrepareNewLine(const int row) noexcept {
  for (size_t i = 0; i < unique_sets.size(); ++i) {
    if (maze_info_.h_walls[row][i]) {
      unique_sets[i] = 0;
    }
  }
}

void MazeCreator::CheckHorizontalWalls(const int row) noexcept {
  for (size_t i = 0; i < unique_sets.size(); ++i) {
    if (CalculateHorizontalWalls(row, unique_sets[i]) == 0) {
      maze_info_.h_walls[row][i] = false;
    }
  }
}

int MazeCreator::CalculateHorizontalWalls(const int row,
                                          const int value) const {
  int amount_of_walls = 0;
  for (size_t i = 0; i < unique_sets.size(); ++i) {
    if (unique_sets[i] == value && !maze_info_.h_walls[row][i]) {
      ++amount_of_walls;
    }
  }
  return amount_of_walls;
}

bool MazeCreator::GenerateRandomBool() {
  static std::default_random_engine generator(std::random_device{}());
  static std::bernoulli_distribution distribution(0.5);
  return distribution(generator);
}

void MazeCreator::MergeEqualSet(const int index) {
  int replaced = unique_sets[index + 1];
  int value = unique_sets[index];
  for (size_t i = 0; i < unique_sets.size(); ++i) {
    if (unique_sets[i] == replaced) {
      unique_sets[i] = value;
    }
  }
}

};  // namespace maze
