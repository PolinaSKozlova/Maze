#ifndef MAZEWIDGET_H
#define MAZEWIDGET_H

#include <QWidget>

#include "QtGui/qpainter.h"
#include "maze_struct.h"

class MazeWidget : public QWidget {
  Q_OBJECT
 public:
  explicit MazeWidget(QWidget *parent = nullptr);

  void PaintMaze(QPainter *p);
  void PaintPath(QPainter *p);
  void SetModel(std::shared_ptr<maze::MazeInfo> mm);
  void FillPath(std::shared_ptr<std::list<maze::Coordinate>> best_path_);
  maze::Coordinate GetStart();
  maze::Coordinate GetEnd();
  void UpdatePoints();

 protected:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;

 signals:
  void StartSolvingPath();

 private:
  void PaintIcon(QPainter *p, QPixmap *icon, int icon_size, int x, int y);
  std::shared_ptr<maze::MazeInfo> maze_model_;
  std::shared_ptr<std::list<maze::Coordinate>> best_path_;
  std::shared_ptr<std::string> base_path_;
  QList<QLine> FillFloors(const std::vector<std::vector<bool>> &input);
  QList<QLine> FillWalls(const std::vector<std::vector<bool>> &input);
  QPointF start_point_;
  QPointF end_point_;
  std::vector<QPointF> path_;
};

#endif  // MAZEWIDGET_H
