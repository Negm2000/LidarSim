#include <rclcpp/rclcpp.hpp>
#include <chrono>
#include "obstacle_detector/monitor_node.hpp"
using namespace std::chrono_literals;

Monitor::Monitor(): Node("monitor_node"), tf_buffer(), tf_listener(tf_buffer)
{
    timer = create_wall_timer(200ms,[&](){control_cycle();});
    marker_pub = create_publisher<visualization_msgs::msg::Marker>("obstacle_marker",1); 
}

void Monitor::control_cycle(){
    
}
