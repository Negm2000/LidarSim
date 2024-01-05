#include "obstacle_detector/detector_node.hpp"
#include <algorithm>
#include <chrono>
using namespace std::placeholders;
using namespace std::chrono_literals;
Detector::Detector()
: Node("detector_node")
{
  sub = create_subscription<sensor_msgs::msg::LaserScan>
    (
      "/scan", rclcpp::SensorDataQoS(), 
      std::bind(&Detector::laser_callback, this, _1)
    );
  static_broadcaster = std::make_shared<tf2_ros::StaticTransformBroadcaster>(this);
}

void Detector::laser_callback(sensor_msgs::msg::LaserScan::UniquePtr msgPtr)
{
  // Store the message in a member variable
  msg = std::move(msgPtr);

  // Find the index of the nearest obstacle
  auto nearest_obstacle = std::min_element(msg->ranges.begin(), msg->ranges.end());
  nearest_obstacle_idx = std::distance(msg->ranges.begin(), nearest_obstacle);

  // Publish a static transform from laser to detected_obstacle
  geometry_msgs::msg::TransformStamped transformStamped;
  transformStamped.header = msg->header;
  transformStamped.child_frame_id = "detected_obstacle";
  float theta = msg->angle_min + msg->angle_increment * nearest_obstacle_idx;
  transformStamped.transform.translation.x = msg->ranges[nearest_obstacle_idx] * std::cos(theta);
  transformStamped.transform.translation.y = msg->ranges[nearest_obstacle_idx] * std::sin(theta);
  static_broadcaster->sendTransform(transformStamped);
}
