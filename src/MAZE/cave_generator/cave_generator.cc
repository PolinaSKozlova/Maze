#include "cave_generator.h"

#include <random>

CaveGenerator::CaveGenerator(int rows, int cols, int probability,
                             BirthRules rules)
    : cave_(Cave(rows, cols)), rules_(rules) {
  FillCaveRandomly(probability);
}

void CaveGenerator::Generate(const int rows, const int cols,
                             const int probability, const BirthRules& rules) {
  cave_ = Cave(rows, cols);
  rules_ = rules;
  FillCaveRandomly(probability);
}

void CaveGenerator::Generate(const std::string& filename,
                             const BirthRules& rules) {
  cave_.ParseCaveFile(filename);
  rules_ = rules;
}

void CaveGenerator::FillCaveRandomly(const int probability) {
  std::random_device device;
  std::default_random_engine engine(device());
  std::uniform_int_distribution<int> distribution(0, 100);

  for (int row_idx = 0; row_idx < cave_.Rows(); ++row_idx) {
    for (int col_idx = 0; col_idx < cave_.Cols(); ++col_idx) {
      cave_.SetValue(row_idx, col_idx, distribution(engine) <= probability);
    }
  }
}

int CaveGenerator::CountNeighbours(const int row_idx, const int col_idx) const {
  int counter = 0;
  for (int row_offset = -1; row_offset <= 1; ++row_offset) {
    for (int col_offset = -1; col_offset <= 1; ++col_offset) {
      if (row_offset == 0 && col_offset == 0) continue;
      int neighbour_row_idx = row_idx + row_offset;
      int neighbour_col_idx = col_idx + col_offset;
      if (neighbour_row_idx < 0 || neighbour_row_idx >= cave_.Rows() ||
          neighbour_col_idx < 0 || neighbour_col_idx >= cave_.Cols() ||
          cave_.GetValue(neighbour_row_idx, neighbour_col_idx)) {
        counter++;
      }
    }
  }
  return counter;
}

bool CaveGenerator::CellOnNextIter(const int row_idx, const int col_idx) const {
  bool is_alive = cave_.GetValue(row_idx, col_idx);
  int n_neighbours = CountNeighbours(row_idx, col_idx);
  if (is_alive) {
    if (n_neighbours < rules_.will_die_if_less) {
      return false;
    }
    return true;
  } else {
    if (n_neighbours > rules_.will_born_if_more) {
      return true;
    }
    return false;
  }
}

void CaveGenerator::NextIter() {
  Cave next_cave(cave_.Rows(), cave_.Cols());
  for (int row_idx = 0; row_idx < cave_.Rows(); ++row_idx) {
    for (int col_idx = 0; col_idx < cave_.Cols(); ++col_idx) {
      next_cave.SetValue(row_idx, col_idx, CellOnNextIter(row_idx, col_idx));
    }
  }
  cave_ = next_cave;
}
