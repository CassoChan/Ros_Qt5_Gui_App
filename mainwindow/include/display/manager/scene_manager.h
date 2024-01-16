#pragma once
#include "config/topology_map.h"
#include "display/point_shape.h"
#include "widgets/nav_goal_widget.h"
#include "widgets/set_pose_widget.h"
#include <QCursor>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <display/virtual_display.h>
namespace Display {
class DisplayManager;
class SceneDisplay : public QGraphicsScene {
private:
  SetPoseWidget *set_nav_pose_widget_;
  QGraphicsView *view_ptr_;
  Display::VirtualDisplay *curr_handle_display_{nullptr};
  DisplayManager *display_manager_;
  NavGoalWidget *nav_goal_widget_;
  std::shared_ptr<QCursor> nav_goal_cursor_ = nullptr;
  TopologyMap topology_map_;

public:
  SceneDisplay(QObject *parent = nullptr);
  virtual ~SceneDisplay();
  void Init(QGraphicsView *view_ptr, DisplayManager *manager);
  void AddOneNavPoint();
  void LoadTopologyMap();

private:
  void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
  void saveTopologyMap();

};
} // namespace Display