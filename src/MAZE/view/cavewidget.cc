#include "cavewidget.h"

#include "QPainter"

CaveWidget::CaveWidget(QWidget *parent) : QWidget{parent} {}

void CaveWidget::paintEvent(QPaintEvent *event) {
  emit ChangedOnCave();
  QPainter painter(this);
  QRectF rectangle(0.0, 0.0, 500.0, 500.0);
  painter.drawRect(rectangle);
  if (cave_model_ != nullptr) {
    PaintCave(&painter);
  }
  update();
}

void CaveWidget::PaintCave(QPainter *painter) {
  Cave cave = *cave_model_.get();
  int cave_length = cave.Cols();
  int cave_height = cave.Rows();

  constexpr int canvas_size = 500;
  int cell_length = canvas_size / cave_length;
  int cell_height = canvas_size / cave_height;

  for (int row_idx = 0; row_idx < cave_height; ++row_idx) {
    for (int col_idx = 0; col_idx < cave_length; ++col_idx) {
      if (cave.GetValue(row_idx, col_idx)) {
        painter->fillRect(col_idx * cell_length, row_idx * cell_height,
                          cell_length, cell_height, Qt::white);
      }
    }
  }
}
