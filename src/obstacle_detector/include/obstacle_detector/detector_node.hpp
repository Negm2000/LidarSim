#include "rclcpp/rclcpp.hpp"
#include <sensor_msgs/msg/laser_scan.hpp>
#include <tf2_ros/static_transform_broadcaster.h>

class Detector : public rclcpp::Node
{
public:
  Detector();
  int nearest_obstacle_idx;

private:
  sensor_msgs::msg::LaserScan::UniquePtr msg;
  rclcpp::TimerBase::SharedPtr timer;
  std::shared_ptr<tf2_ros::StaticTransformBroadcaster> static_broadcaster;
  rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr sub;
  void timer_callback();
  void laser_callback(sensor_msgs::msg::LaserScan::UniquePtr msgPtr);
};
