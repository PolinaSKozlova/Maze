#include "mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QThread>
#include <iostream>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->widget, &MazeWidget::StartSolvingPath, this,
          &MainWindow::GotSignalSolvePath);
  connect(ui->cavewidget, &CaveWidget::ChangedOnCave, this,
          &MainWindow::GotSignalCaveOn);
  timer_ = new QTimer(this);
  connect(timer_, &QTimer::timeout, this, &MainWindow::NextIter);
  ui->tabWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow() {
  delete timer_;
  delete ui;
}

void MainWindow::SendInfoToWidget(std::shared_ptr<maze::MazeInfo> mm) {
  ui->widget->UpdatePoints();
  ui->widget->SetModel(mm);
}

maze::Coordinate MainWindow::GetStartFromWidget() {
  return ui->widget->GetStart();
}

maze::Coordinate MainWindow::GetEndFromWidget() { return ui->widget->GetEnd(); }

void MainWindow::SendPathToWidget(
    std::shared_ptr<std::list<maze::Coordinate> > bp) {
  ui->widget->FillPath(bp);
}

void MainWindow::on_OpenFileButton_clicked() {
  std::string path = QCoreApplication::applicationDirPath().toStdString();
  QString inFileName = QFileDialog::getOpenFileName(
      this, "Open file", QString::fromStdString(path));
  if (!inFileName.isNull()) {
    emit OpenFile(inFileName.toStdString());
  } else {
    QMessageBox::critical(this, "Error!", "The file does not exist!");
  }
}

void MainWindow::on_GeneataMazeButton_clicked() {
  int h = ui->height->value();
  int w = ui->width->value();
  emit GenerateMaze(h, w);
}

void MainWindow::on_SaveButton_clicked() {
  QDir::currentPath();
  QString new_filename = QFileDialog::getSaveFileName(0, "Save", "", "*.txt");
  if (new_filename.isEmpty()) {
    return;
  }
  try {
    emit SaveFile(new_filename.toStdString());
  } catch (const std::exception &exc) {
    QMessageBox::critical(this, "Warning", exc.what());
  }
}

void MainWindow::GotSignalSolvePath() {
  emit SolvePath(GetStartFromWidget(), GetEndFromWidget());
}

void MainWindow::GotSignalCaveOn() { ui->widget->UpdatePoints(); }

void MainWindow::SendCave(std::shared_ptr<Cave> cave) {
  ui->cavewidget->SetModel(cave);
}

void MainWindow::ShowMessage() {
  QMessageBox msg_box;
  QPixmap gandalf(":/icons/gandalf2.png");
  msg_box.setIconPixmap(gandalf.scaled(640, 480));
  ui->widget->UpdatePoints();
  msg_box.exec();
}

void MainWindow::on_GenerateCaveButton_clicked() {
  int height = ui->height_input->text().toInt();
  int width = ui->width_input->text().toInt();
  int probability = ui->bc_input->text().toInt();
  int die_if_less = ui->die_if_less_input->text().toInt();
  int born_if_more = ui->born_if_more_input->text().toInt();
  if (height > 0 && width > 0) {
    emit GenerateCave(height, width, probability, {die_if_less, born_if_more});
  }
}

void MainWindow::on_NextStepButton_clicked() { emit NextIter(); }

void MainWindow::on_OpenCaveButton_clicked() {
  std::string path = QCoreApplication::applicationDirPath().toStdString();
  QString inFileName = QFileDialog::getOpenFileName(
      this, "Open file", QString::fromStdString(path));
  if (!inFileName.isNull()) {
    emit OpenCaveFile(inFileName.toStdString(),
                      {ui->die_if_less_input->text().toInt(),
                       ui->born_if_more_input->text().toInt()});
  } else {
    QMessageBox::critical(this, "Error!", "The file does not exist!");
  }
}

void MainWindow::on_NextStepAutoButton_toggled(bool checked) {
  int ms = ui->N_input->text().toInt();
  if (checked) {
    timer_->start(ms);
  } else {
    timer_->stop();
  }
}
