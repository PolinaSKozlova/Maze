#include "mazewidget.h"

#include <QtGui>
#include <iostream>

#include "QtWidgets/qlabel.h"
#include "mainwindow.h"
#include "maze_solution/maze_solution.h"

MazeWidget::MazeWidget(QWidget *parent) : QWidget{parent} {}

void MazeWidget::PaintMaze(QPainter *p) {
  QPen pen(Qt::white);  // цвет для стен
  pen.setWidth(2);
  p->setPen(pen);
  QRectF rectangle(0.0, 0.0, 500.0, 500.0);
  p->drawRect(rectangle);
  if (maze_model_ != nullptr) {
    QList<QLine> draw_floors = FillFloors(maze_model_->h_walls);
    QList<QLine> draw_walls = FillWalls(maze_model_->v_walls);
    p->drawLines(draw_floors);
    p->drawLines(draw_walls);
  }
}

void MazeWidget::SetModel(std::shared_ptr<maze::MazeInfo> mm) {
  maze_model_ = mm;
  update();
}

void MazeWidget::FillPath(
    std::shared_ptr<std::list<maze::Coordinate>> best_path_) {
  float h_scale = 500.0 / maze_model_->width;
  float v_scale = 500.0 / maze_model_->height;
  QPointF point;
  for (auto it = best_path_.get()->begin(); it != best_path_.get()->end();
       ++it) {
    point.setX(it->GetX() * h_scale + (h_scale / 2));
    point.setY(it->GetY() * v_scale + (v_scale / 2));
    path_.push_back(point);
  }
  update();
}

maze::Coordinate MazeWidget::GetStart() {
  float x = 0;
  float y = 0;
  if (maze_model_.get() != nullptr) {
    x = start_point_.x() / (500.0 / maze_model_->width);
    y = start_point_.y() / (500.0 / maze_model_->height);
  }
  return maze::Coordinate(x, y);
}

maze::Coordinate MazeWidget::GetEnd() {
  float x = 0;
  float y = 0;
  if (maze_model_.get() != nullptr) {
    x = end_point_.x() / (500.0 / maze_model_->width);
    y = end_point_.y() / (500.0 / maze_model_->height);
  }
  return maze::Coordinate(x, y);
}

void MazeWidget::UpdatePoints() {
  start_point_ = QPointF();
  end_point_ = QPointF();
}

void MazeWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  QPixmap cat(":/icons/cat.png");
  QPixmap mouse(":/icons/mouse.png");
  PaintMaze(&painter);
  if (maze_model_ != nullptr) {
    size_t max = (maze_model_->width > maze_model_->height)
                     ? maze_model_->width
                     : maze_model_->height;
    int icon_size = 500.0 / max;
    if (!start_point_.isNull()) {
      PaintIcon(&painter, &cat, icon_size, GetStart().GetX(),
                GetStart().GetY());
      //      update();
      start_point_ = QPointF();
    }
    if (!end_point_.isNull()) {
      PaintIcon(&painter, &mouse, icon_size, GetEnd().GetX(), GetEnd().GetY());
      //      update();
    }
  }
  if (!path_.empty()) {
    PaintPath(&painter);
  }
}

void MazeWidget::PaintPath(QPainter *p) {
  QPen pen(Qt::yellow);  // цвет для пути
  pen.setWidth(2);
  p->setPen(pen);
  p->drawPolyline(path_.data(), path_.size());
  path_.clear();
}

void MazeWidget::mousePressEvent(QMouseEvent *event) {
  int count = 0;
  if (event->button() == Qt::LeftButton) {
    if (maze_model_ != nullptr) {
      if (!start_point_.isNull()) {
        end_point_ = event->pos();
        count++;
        if (count == 1) {
          emit StartSolvingPath();
          // start_point_ = QPointF();
        }
      } else {
        start_point_ = event->pos();
      }
    }
  }
}

void MazeWidget::PaintIcon(QPainter *p, QPixmap *icon, int icon_size, int x,
                           int y) {
  x = x * (500.0 / maze_model_->width);
  y = y * (500.0 / maze_model_->height);
  p->drawPixmap(x, y, icon->scaled(icon_size, icon_size));

  //  QLabel label;
  //  label.setPixmap(*icon);
  //  label.show();
}

QList<QLine> MazeWidget::FillFloors(
    const std::vector<std::vector<bool>> &input) {
  float h_scale = 500.0 / maze_model_->width;
  float v_scale = 500.0 / maze_model_->height;
  QLine line;
  QList<QLine> to_build;

  for (size_t i = 0; i < maze_model_->height; ++i) {
    for (size_t j = 0; j < maze_model_->width; ++j) {
      float x1, x2, y1, y2;

      if (input[i][j]) {
        x1 = j * h_scale + 1;
        x2 = (j + 1) * h_scale;
        y1 = (i + 1) * v_scale;
        y2 = (i + 1) * v_scale;
        line.setLine(x1, y1, x2, y2);
        to_build.push_back(line);
      }
    }
  }
  return to_build;
}

QList<QLine> MazeWidget::FillWalls(
    const std::vector<std::vector<bool>> &input) {
  float h_scale = 500.0 / maze_model_->width;
  float v_scale = 500.0 / maze_model_->height;
  QLine line;
  QList<QLine> to_build;
  for (size_t i = 0; i < maze_model_->height; ++i) {
    for (size_t j = 0; j < maze_model_->width; ++j) {
      float x1, x2, y1, y2;

      if (input[i][j]) {
        x1 = (j + 1) * h_scale;
        x2 = (j + 1) * h_scale;
        y1 = i * v_scale + 1;
        y2 = (i + 1) * v_scale;
        line.setLine(x1, y1, x2, y2);
        to_build.push_back(line);
      }
    }
  }
  return to_build;
}
