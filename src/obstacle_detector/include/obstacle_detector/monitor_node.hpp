
#ifndef OBSTACLE_DETECTOR_MONITOR_NODE_HPP_
#define OBSTACLE_DETECTOR_MONITOR_NODE_HPP_

#include <rclcpp/rclcpp.hpp>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <visualization_msgs/msg/marker.hpp>

class Monitor: public rclcpp::Node
{
private:
    tf2::BufferCore tf_buffer;
    tf2_ros::TransformListener tf_listener;
    rclcpp::TimerBase::SharedPtr timer;
    rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr marker_pub;
    void control_cycle();
    bool isSimulation;
    std::string base_frame;
public:
    Monitor();
};

#endif // OBSTACLE_DETECTOR_MONITOR_NODE_HPP_