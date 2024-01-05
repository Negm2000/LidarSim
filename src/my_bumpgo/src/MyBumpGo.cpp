#include "my_bumpgo/MyBumpGo.hpp"
#include <chrono>
using namespace Bump;
using namespace std::chrono_literals;
using std::placeholders::_1;
#define DEG2IDX(offset_degrees, degrees_per_idx) (offset_degrees * M_PI / 180) / degrees_per_idx

MyBumpGo::MyBumpGo()
: Node("my_bumpgo"), state_(FORWARD)
{
  // Create a timer that calls controlCycle() every 50ms
  timer_ = create_wall_timer(50ms, [&]() {controlCycle();});

  // Create a subscriber to /scan topic
  sub_ = create_subscription<sensor_msgs::msg::LaserScan>(
    "input_scan",
    rclcpp::SensorDataQoS(),
    std::bind(&MyBumpGo::scanCallback, this, _1)
  );
  // Create a publisher to /output_vel topic
  pub_ = create_publisher<geometry_msgs::msg::Twist>(
    "output_vel",
    rclcpp::QoS(rclcpp::KeepLast(10))
  );

  state_ts_ = now();
}
// Helper functions

void MyBumpGo::goState(State s)
{
  state_ = s;
  state_ts_ = now();
}

// Check if there is an obstacle in front of the robot
// Front is anything within 20 degrees of the center
bool MyBumpGo::check_obstacle()
{

  int offset = DEG2IDX(20, msg_->angle_increment);

  size_t center_pos = msg_->ranges.size() / 2;
  for (size_t i = center_pos - offset; i < center_pos + offset; i++) {
    if (msg_->ranges[i] < OBSTACLE_DISTANCE) {
      return true;
    }
  }

  return false;
}

bool MyBumpGo::check_backward2turn()
{
  return now() - state_ts_ > BACKING_TIME;
}

bool MyBumpGo::check_turn2forward(float farthest_obstacle)
{
  size_t center_pos = msg_->ranges.size() / 2;
  return msg_->ranges[center_pos] > (farthest_obstacle - 0.3);
}

bool MyBumpGo::shouldStop()
{
  return now() - msg_->header.stamp > SCAN_TIMEOUT;
}


bool MyBumpGo::check_stop_2_forward()
{
  return now() - msg_->header.stamp > SCAN_TIMEOUT;
}


void MyBumpGo::scanCallback(sensor_msgs::msg::LaserScan::UniquePtr msg)
{
  msg_ = std::move(msg);
}

void MyBumpGo::controlCycle()
{
  // Do nothing until the first sensor read
  if (msg_ == nullptr) {return;}
  if (shouldStop()) {
    goState(STOP);
    return;
  }
  geometry_msgs::msg::Twist command;

  switch (state_) {
    case FORWARD:
      command.linear.x = SPEED_LINEAR;
      if (check_obstacle()) {goState(BACKWARD);}
      break;
    case BACKWARD:
      command.linear.x = -SPEED_LINEAR;
      if (check_backward2turn()) {goState(TURN);}
      break;
    case TURN: {
        command.angular.z = SPEED_ANGULAR;
        // if(check_obstacle()){break;}
        auto farthest_obstacle = std::max_element(msg_->ranges.begin(), msg_->ranges.end());
        if (check_turn2forward(*farthest_obstacle)) {goState(FORWARD);}
        break;
      }
    case STOP:
      if (check_stop_2_forward()) {goState(FORWARD);}
      break;
    default:
      break;
  }

  pub_->publish(command);
}
