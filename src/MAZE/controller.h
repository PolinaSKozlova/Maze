#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "../cave_generator/cave_generator.h"  // TODO(weldonfe): smth might be wrong w/code style here
#include "../maze_creator/maze_ideal.h"
#include "../maze_reader/maze_ordinary.h"
#include "../view/mainwindow.h"
#include "maze_solution/maze_solution.h"

class Controller : public QObject {
  Q_OBJECT
 public:
  explicit Controller(QObject* parent = nullptr);
  void run();

 public slots:
  void OpenFile(const std::string& filename);
  void GenerateMaze(int height, int width);
  void SaveFile(const std::string& filepath);
  void GenerateCave(int rows, int cols, int probability, BirthRules rules);
  void SolvePath(maze::Coordinate A, maze::Coordinate B);
  void NextIter();
  void NextIterAuto();
  void OpenCaveFile(const std::string& filename, BirthRules rules);

 private:
  void FindBasePath();
  MainWindow w;
  maze::MazeReader mr;
  maze::MazeCreator mc;
  maze::MazeSolution ms;
  CaveGenerator cg;
  std::string base_path_;
};

#endif  // CONTROLLER_H
