#include "obstacle_detector/detector_node.hpp"
#include "obstacle_detector/monitor_node.hpp"
#include <memory>
#include <rclcpp/executor.hpp>
int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  std::shared_ptr<Detector> detector_node = std::make_shared<Detector>();
  std::shared_ptr<Monitor> monitor_node = std::make_shared<Monitor>();
  rclcpp::executors::SingleThreadedExecutor executor;
  executor.add_node(detector_node);
  executor.add_node(monitor_node);
  executor.spin();
  rclcpp::shutdown();
}
