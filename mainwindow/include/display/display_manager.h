/*
 * @Author: chengyang chengyangkj@outlook.com
 * @Date: 2023-03-29 14:21:31
 * @LastEditors: chengyangkj chengyangkj@qq.com
 * @LastEditTime: 2023-10-15 09:31:36
 * @FilePath:
 * ////include/display/display_manager.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H
#include "algorithm.h"
#include "display_cost_map.h"
#include "display_occ_map.h"
#include "display_path.h"
#include "display_tag.h"
#include "factory_display.h"
#include "laser_points.h"
#include "particle_points.h"
#include "point_shape.h"
#include "region.h"
#include "widgets/set_pose_widget.h"
#include <Eigen/Dense>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <any>
#include <functional>
#include <map>
#define DISPLAY_ROBOT "Robot"
#define DISPLAY_MAP "OccupyMap"
#define DISPLAY_LOCAL_COST_MAP "LocalCostMap"
#define DISPLAY_GLOBAL_COST_MAP "GlobalCostMap"
#define DISPLAY_GLOBAL_PATH "GlobalPath"
#define DISPLAY_LOCAL_PATH "LocalPath"
#define DISPLAY_LASER "LaserScan"
#define DISPLAY_PARTICLE "Particle"
#define DISPLAY_REGION "Region"
#define DISPLAY_TAG "Tag"
#define DISPLAY_GOAL "GoalPose"

// group
#define GROUP_MAP "Group_Map"

namespace Display {
class DisplayManager : public QObject {
  Q_OBJECT
private:
  std::map<std::string, std::any> display_map_;

  Eigen::Vector3f robot_pose_{0, 0, 0};
  Eigen::Vector3f robot_pose_goal_{0, 0, 0};
  OccupancyMap map_data_;
  std::string focus_display_;
  RobotPose local_cost_world_pose_;
  CostMap local_cost_map_;
  double global_scal_value_ = 1;
  bool is_reloc_mode_{false};
  QGraphicsView *graphics_view_ptr_;
  SetPoseWidget *set_reloc_pose_widget_;
  SetPoseWidget *set_nav_pose_widget_;
signals:
  void cursorPosMap(QPointF);
  void DisplayRobotPoseWorld(Eigen::Vector3f pose);
  void signalPub2DPose(const RobotPose &pose);
  void signalPub2DGoal(const RobotPose &pose);
public slots:
  void updateScaled(double value);
  void SetRelocPose();
  void SetNavPose();
  void slotRobotScenePoseChanged(const RobotPose &pose);
  void slotNavGoalScenePoseChanged(const RobotPose &pose);
  void slotSetRobotPose(const RobotPose &pose);
  void slotSetNavPose(const RobotPose &pose);

private:
  Eigen::Vector3f wordPose2Scene(const Eigen::Vector3f &point);
  QPointF wordPose2Scene(const QPointF &point);
  QPointF wordPose2Map(const QPointF &pose);
  void FocusDisplay(const std::string &display_name);
  void InitUi();
  std::vector<Eigen::Vector2f>
  transLaserPoint(const std::vector<Eigen::Vector2f> &point);
  QPushButton *btn_move_focus_;

public:
  DisplayManager(QGraphicsView *viewer);
  ~DisplayManager();
  VirtualDisplay *GetDisplay(const std::string &name);
  bool UpdateDisplay(const std::string &display_name, const std::any &data);
  void UpdateRobotPose(const Eigen::Vector3f &pose);
  bool SetDisplayConfig(const std::string &config_name, const std::any &data);
  Eigen::Vector3f wordPose2Map(const Eigen::Vector3f &pose);
  void SetRelocMode(bool is_move);
  void SetNavGoalMode(bool is_start);

  void SetFocusOn(const std::string &display_name) {
    focus_display_ = display_name;
  }
};

} // namespace Display

#endif