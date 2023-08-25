#ifndef MAZEAPP_CAVES_CAVE_H_
#define MAZEAPP_CAVES_CAVE_H_

#include <iostream>
#include <vector>

class Cave {
 public:
  using vector = std::vector<bool>;
  explicit Cave(int rows, int cols)
      : rows_(rows), cols_(cols), cells_(rows * cols, false) {
    CheckCaveSize();
  }

  Cave(const Cave& other)
      : rows_(other.rows_), cols_(other.cols_), cells_(other.cells_) {}

  Cave(Cave&& other) {
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(cells_, other.cells_);
  }

  Cave& operator=(const Cave& other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    cells_ = other.cells_;
    return *this;
  }

  Cave& operator=(Cave&& other) {
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(cells_, other.cells_);
    return *this;
  }

  void ParseCaveFile(const std::string& filename);

  int Rows() const { return rows_; }
  int Cols() const { return cols_; }
  vector GetCells() const { return cells_; }

  void SetValue(int row_idx, int col_idx, bool value) {
    cells_[row_idx * cols_ + col_idx] = value;
  }

  bool GetValue(int row_idx, int col_idx) const {
    return cells_[row_idx * cols_ + col_idx];
  }

 private:
  void ReadCaveSize(const std::string& line);
  void CheckCaveSize() const;
  void FillCells(const std::string& line, int& pos);
  bool CheckNumberBool(int number) const noexcept;
  int rows_;
  int cols_;
  vector cells_;
};

std::ostream& operator<<(std::ostream& os, Cave& cave);

#endif  //  MAZEAPP_CAVES_CAVE_H_
