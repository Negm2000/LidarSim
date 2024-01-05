#include <rclcpp/rclcpp.hpp>
#include <memory>
#include "my_bumpgo/MyBumpGo.hpp"
using namespace Bump;

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<MyBumpGo>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
