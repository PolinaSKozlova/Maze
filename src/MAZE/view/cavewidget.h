#ifndef CAVEWIDGET_H
#define CAVEWIDGET_H

#include <QWidget>

#include "cave_generator/cave_generator.h"

class CaveWidget : public QWidget {
  Q_OBJECT
 public:
  explicit CaveWidget(QWidget *parent = nullptr);
  void PaintCave(QPainter *painter);
  void SetModel(std::shared_ptr<Cave> cave) { cave_model_ = cave; }

 protected:
  void paintEvent(QPaintEvent *event) override;

 signals:
  void ChangedOnCave();

 private:
  std::shared_ptr<Cave> cave_model_;
};

#endif  // CAVEWIDGET_H
