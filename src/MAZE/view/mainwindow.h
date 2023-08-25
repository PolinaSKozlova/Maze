#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "cave_generator/cave_generator.h"
#include "maze_struct.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void SendInfoToWidget(std::shared_ptr<maze::MazeInfo> mm);
  maze::Coordinate GetStartFromWidget();
  maze::Coordinate GetEndFromWidget();
  void SendPathToWidget(std::shared_ptr<std::list<maze::Coordinate>> bp);
  void SendCave(std::shared_ptr<Cave> cave);
  void ShowMessage();
  void SendBasePath(std::shared_ptr<std::string> bpth);

 public slots:
  void GotSignalSolvePath();
  void GotSignalCaveOn();

 signals:
  void OpenFile(const std::string &filename);
  void GenerateMaze(int height, int width);
  void SaveFile(const std::string &filepath);
  void SolvePath(maze::Coordinate A, maze::Coordinate B);
  void GenerateCave(int rows, int cols, int probability, BirthRules rules);
  void NextIter();
  void NextIterAuto(int ms);
  void OpenCaveFile(const std::string &filename, BirthRules rules);

 private slots:
  void on_OpenFileButton_clicked();
  void on_GeneataMazeButton_clicked();
  void on_SaveButton_clicked();
  void on_GenerateCaveButton_clicked();
  void on_NextStepButton_clicked();
  void on_OpenCaveButton_clicked();
  void on_NextStepAutoButton_toggled(bool checked);

 private:
  Ui::MainWindow *ui;
  QTimer *timer_;
};
#endif  // MAINWINDOW_H
