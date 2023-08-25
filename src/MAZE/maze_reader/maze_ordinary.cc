#include "maze_ordinary.h"

#include <filesystem>
#include <fstream>
#include <regex>
#include <sstream>

namespace maze {
void MazeReader::GenerateMaze(const std::string& filepath) {
  std::filesystem::path absolutePath = std::filesystem::absolute(filepath);
  data_.filepath = absolutePath.string();
  ParseFile();
}

void MazeReader::ParseFile() {
  std::ifstream fin;
  std::string line{};
  fin.open(data_.filepath);
  if (!fin.is_open()) throw std::invalid_argument("Can't open file");
  size_t counter{1};
  size_t pos{0};
  while (!fin.eof()) {
    if (counter > data_.height * 2 + 2) break;
    getline(fin, line);
    if (counter == 1) {
      ReadSize(line);
      data_.v_walls.resize(data_.height);
      data_.h_walls.resize(data_.height);
    } else if (counter < data_.height + 2) {
      data_.v_walls[pos++] = ReadWalls(line);
    } else if (counter == data_.height + 2) {
      ++counter;
      pos = 0;
      continue;
    }
    if (counter > data_.height + 2) {
      data_.h_walls[pos++] = ReadWalls(line);
    }
    ++counter;
  }
  fin.close();
}

std::pair<std::vector<std::vector<bool>>, std::vector<std::vector<bool>>>
MazeReader::GetWalls() const {
  return std::make_pair(data_.v_walls, data_.h_walls);
}

std::pair<size_t, size_t> MazeReader::GetSize() const {
  return std::make_pair(data_.height, data_.width);
}

MazeInfo MazeReader::GetData() const { return data_; }

void MazeReader::ReadSize(const std::string& line) {
  if (!std::regex_match(line, std::regex("(\\d+?[ ]?\\d+)")))
    throw std::invalid_argument("Incorrect size");
  std::istringstream iss(line);
  iss >> data_.height >> data_.width;
  CheckSize();
}

void MazeReader::CheckSize() const {
  if (!data_.height || !data_.width)
    throw std::invalid_argument("Minimal size should be 1x1");
  if (data_.height > 50 || data_.width > 50)
    throw std::invalid_argument("Maximum size for maze is 50x50");
}

std::vector<bool> MazeReader::ReadWalls(const std::string& line) {
  std::istringstream iss(line);
  std::string maze_line{};
  std::vector<bool> result(data_.width);
  size_t pos{0};
  while (iss >> maze_line) {
    std::istringstream sub_iss(maze_line);
    std::string sub_token;
    getline(sub_iss, sub_token, ' ');
    if (!sub_token.empty()) {
      if (!CheckNumberBool(std::stoi(sub_token)))
        throw std::invalid_argument("Incorrect wall index");
      result[pos++] = std::stoi(sub_token);
    }
  }
  if (pos != data_.width)
    throw std::invalid_argument("Incorrect number of walls ");
  return result;
}

bool MazeReader::CheckNumberBool(int sym) const noexcept {
  return (sym == 0 || sym == 1);
}
};  // namespace maze
