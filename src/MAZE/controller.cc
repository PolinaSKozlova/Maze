#include "controller.h"

#include <iostream>

#include "QtWidgets/qapplication.h"

Controller::Controller(QObject* parent) : QObject{parent} {}

void Controller::run() {
  // Maze
  connect(&w, &MainWindow::OpenFile, this, &Controller::OpenFile);
  connect(&w, &MainWindow::GenerateMaze, this, &Controller::GenerateMaze);
  connect(&w, &MainWindow::SaveFile, this, &Controller::SaveFile);
  connect(&w, &MainWindow::SolvePath, this, &Controller::SolvePath);
  // Cave
  connect(&w, &MainWindow::GenerateCave, this, &Controller::GenerateCave);
  connect(&w, &MainWindow::NextIter, this, &Controller::NextIter);
  connect(&w, &MainWindow::NextIterAuto, this, &Controller::NextIterAuto);
  connect(&w, &MainWindow::OpenCaveFile, this, &Controller::OpenCaveFile);
  // Ui
  w.setFixedSize(880, 600);
  w.setWindowTitle("It is aMAZEing!");
  w.show();
}

void Controller::OpenFile(const std::string& filename) {
  mr.GenerateMaze(filename);
  maze::MazeInfo tmp = mr.GetData();
  w.SendInfoToWidget(std::make_shared<maze::MazeInfo>(tmp));
  ms.SetMaze(std::make_shared<maze::MazeInfo>(tmp));
}

void Controller::GenerateMaze(int height, int width) {
  mc.GenerateMaze(height, width);
  maze::MazeInfo tmp = mc.GetMazeInfo();
  w.SendInfoToWidget(std::make_shared<maze::MazeInfo>(tmp));
  ms.SetMaze(std::make_shared<maze::MazeInfo>(tmp));
  //  w.update();
}

void Controller::SaveFile(const std::string& filepath) {
  mc.SaveMaze(filepath);
}

void Controller::SolvePath(maze::Coordinate A, maze::Coordinate B) {
  try {
    ms.FindPath(A, B);
  } catch (std::exception e) {
    w.ShowMessage();
  }
  std::list<maze::Coordinate> way = ms.GetPath();
  w.SendPathToWidget(std::make_shared<std::list<maze::Coordinate>>(way));
}

void Controller::GenerateCave(int rows, int cols, int probability,
                              BirthRules rules) {
  cg.Generate(rows, cols, probability, rules);
  auto tmp_cave = std::make_shared<Cave>(cg.GetCave());
  w.SendCave(tmp_cave);
}

void Controller::NextIter() {
  cg.NextIter();
  auto tmp_cave = std::make_shared<Cave>(cg.GetCave());
  w.SendCave(tmp_cave);
}

void Controller::NextIterAuto() {
  cg.NextIter();
  auto tmp_cave = std::make_shared<Cave>(cg.GetCave());
  w.SendCave(tmp_cave);
}

void Controller::OpenCaveFile(const std::string& filename, BirthRules rules) {
  cg.Generate(filename, rules);
  auto tmp_cave = std::make_shared<Cave>(cg.GetCave());
  w.SendCave(tmp_cave);
}
