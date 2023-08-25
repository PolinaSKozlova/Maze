#include "cave.h"

#include <filesystem>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>

void Cave::ParseCaveFile(const std::string& filename) {
  if (!cells_.empty()) cells_.clear();
  std::ifstream fin;
  std::string line{};
  int position{0};
  std::filesystem::path absolutePath = std::filesystem::absolute(filename);
  fin.open(absolutePath.string());
  if (!fin.is_open()) throw std::invalid_argument("File not found");
  int counter{1};
  while (!fin.eof()) {
    getline(fin, line);
    if (counter == 1) {
      ReadCaveSize(line);
      cells_.resize(rows_ * cols_);
    } else if (counter < rows_ + 2) {
      FillCells(line, position);
    } else {
      break;
    }
    ++counter;
  }
  fin.close();
}

void Cave::ReadCaveSize(const std::string& line) {
  if (!std::regex_match(line, std::regex("(\\d+?[ ]?\\d+)")))
    throw std::invalid_argument("Incorrect size");
  std::istringstream iss(line);
  iss >> rows_ >> cols_;
  CheckCaveSize();
}

void Cave::CheckCaveSize() const {
  if (rows_ < 1 || cols_ < 1)
    throw std::invalid_argument("Minimal size should be 1x1");
  if (rows_ > 50 || cols_ > 50)
    throw std::invalid_argument("Maximum size for maze is 50x50");
}

void Cave::FillCells(const std::string& line, int& pos) {
  std::istringstream iss(line);
  std::string cave_line{};
  while (iss >> cave_line) {
    std::istringstream sub_iss(cave_line);
    std::string sub_token;
    getline(sub_iss, sub_token, ' ');
    if (!sub_token.empty()) {
      if (!CheckNumberBool(std::stoi(sub_token)))
        throw std::invalid_argument("Incorrect wall index");
      cells_[pos++] = std::stoi(sub_token);
    }
  }
}

bool Cave::CheckNumberBool(int number) const noexcept {
  return (number == 0 || number == 1);
}

std::ostream& operator<<(std::ostream& os, Cave& cave) {
  for (int row_idx = 0; row_idx < cave.Rows(); ++row_idx) {
    for (int col_idx = 0; col_idx < cave.Cols(); ++col_idx) {
      os << (cave.GetValue(row_idx, col_idx) ? '#' : ' ');
    }
    os << '\n';
  }
  return os;
}
