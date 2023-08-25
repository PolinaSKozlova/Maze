#ifndef MAZEAPP_CAVES_CAVEGENERATOR_H_
#define MAZEAPP_CAVES_CAVEGENERATOR_H_

#include <random>

#include "cave.h"

struct BirthRules {
  int will_die_if_less;
  int will_born_if_more;
};

class CaveGenerator {
 public:
  explicit CaveGenerator(int rows, int cols, int probability, BirthRules rules);

  explicit CaveGenerator(Cave& cave, BirthRules rules)
      : cave_(cave), rules_(rules) {}

  CaveGenerator() : CaveGenerator(50, 50, 42, {3, 4}) {}

  void NextIter();
  void SetCave(const Cave& cave) { cave_ = cave; }
  Cave& GetCave() { return cave_; }

  void Generate(const int rows, const int cols, const int probability,
                const BirthRules& rules);
  void Generate(const std::string& filename, const BirthRules& rules);

 private:
  void FillCaveRandomly(const int probability);
  int CountNeighbours(const int row_idx, const int col_idx) const;
  bool CellOnNextIter(const int row_idx, const int col_idx) const;

  Cave cave_;
  BirthRules rules_;
};

#endif  //  MAZEAPP_CAVES_CAVEGENERATOR_H_
