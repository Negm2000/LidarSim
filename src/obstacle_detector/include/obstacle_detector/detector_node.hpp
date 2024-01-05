#ifndef OBSTACLE_DETECTOR_DETECTOR_NODE_HPP_
#define OBSTACLE_DETECTOR_DETECTOR_NODE_HPP_

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
  std::shared_ptr<tf2_ros::StaticTransformBroadcaster> static_broadcaster;
  rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr sub;
  void laser_callback(sensor_msgs::msg::LaserScan::UniquePtr msgPtr);
};

#endif // OBSTACLE_DETECTOR_DETECTOR_NODE_HPP_
