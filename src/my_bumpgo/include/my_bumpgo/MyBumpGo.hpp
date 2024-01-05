#ifndef MY_BUMPGO_MYBUMPGO_HPP_
#define MY_BUMPGO_MYBUMPGO_HPP_

#include <rclcpp/rclcpp.hpp>
#include "geometry_msgs/msg/twist.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include <memory>
using namespace std::chrono_literals;

namespace Bump
{
class MyBumpGo : public rclcpp::Node
{
public:
  MyBumpGo();
  enum State {FORWARD, BACKWARD, TURN, STOP};

private:
  void scanCallback(sensor_msgs::msg::LaserScan::UniquePtr msg);
  void controlCycle();
  // Helper functions for state transitions
  void goState(State s);
  bool shouldStop();
  bool check_obstacle();
  bool check_backward2turn();
  bool check_turn2forward(float);
  bool check_stop_2_forward();

  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub_;
  rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr sub_;
  rclcpp::TimerBase::SharedPtr timer_;
  sensor_msgs::msg::LaserScan::UniquePtr msg_;
  rclcpp::Time state_ts_;
  State state_;
  const rclcpp::Duration TURNING_TIME {2s};
  const rclcpp::Duration BACKING_TIME {2s};
  const rclcpp::Duration SCAN_TIMEOUT {1s};

  static constexpr float SPEED_LINEAR = 1.0f;
  static constexpr float SPEED_ANGULAR = 0.5f;
  static constexpr float OBSTACLE_DISTANCE = 1.0f;

};
}  // namespace My


#endif // MY_BUMPGO_MYBUMPGO_HPP_
