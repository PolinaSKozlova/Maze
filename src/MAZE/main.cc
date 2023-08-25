#include <QApplication>

#include "controller.h"
#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  a.setWindowIcon(QIcon(":icons/maze.png"));
  Controller controller;
  controller.run();
  return a.exec();
}
