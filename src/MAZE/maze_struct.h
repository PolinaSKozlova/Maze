#ifndef MAZEAPP_MAZE_STRUCT_H_
#define MAZEAPP_MAZE_STRUCT_H_

#include <iostream>
#include <string>
#include <vector>

namespace maze {
class Coordinate {
 public:
  Coordinate() = default;
  explicit Coordinate(int x, int y) : x_(x), y_(y) {}
  explicit Coordinate(std::pair<int, int> xy) : x_(xy.first), y_(xy.second) {}
  Coordinate(const Coordinate& other) { *this = other; }
  Coordinate(Coordinate&& other) { *this = std::move(other); }
  ~Coordinate() = default;
  Coordinate& operator=(const Coordinate& other) {
    x_ = other.x_;
    y_ = other.y_;
    return *this;
  }
  Coordinate& operator=(Coordinate&& other) {
    std::swap(x_, other.x_);
    std::swap(y_, other.y_);
    return *this;
  }

  bool operator==(const Coordinate& other) const noexcept {
    return x_ == other.x_ && y_ == other.y_;
  }
  bool operator!=(const Coordinate& other) const noexcept {
    return !(*this == other);
  }
  bool operator>(const Coordinate& other) const noexcept {
    return !(*this < other) && !(*this == other);
  }
  bool operator<(const Coordinate& other) const noexcept {
    if (x_ < other.x_) return true;
    if (x_ == other.x_ && y_ < other.y_) return true;
    return false;
  }
  std::pair<int, int> GetXY() const noexcept { return std::make_pair(x_, y_); }
  int GetX() const { return x_; }
  int GetY() const { return y_; }
  Coordinate Up() const { return Coordinate(x_, y_ - 1); }
  Coordinate Down() const { return Coordinate(x_, y_ + 1); }
  Coordinate Left() const { return Coordinate(x_ - 1, y_); }
  Coordinate Right() const { return Coordinate(x_ + 1, y_); }
  bool IsValid(size_t height, size_t width) {
    return x_ >= 0 && x_ < static_cast<int>(width) && y_ >= 0 &&
           y_ < static_cast<int>(height);
  }

 private:
  int x_{};
  int y_{};
};

struct MazeInfo {
  size_t height{};
  size_t width{};
  std::vector<std::vector<bool>> v_walls{};
  std::vector<std::vector<bool>> h_walls{};
  std::string filepath{};
};
};  // namespace maze

#endif  // MAZEAPP_MAZE_STRUCT_H_
