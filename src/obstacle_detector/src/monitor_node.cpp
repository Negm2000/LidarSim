#include <rclcpp/rclcpp.hpp>
#include <chrono>
#include "obstacle_detector/monitor_node.hpp"
#include "geometry_msgs/msg/transform_stamped.h"

using namespace std::chrono_literals;

Monitor::Monitor(): Node("monitor_node"), tf_listener(tf_buffer)
{
    declare_parameter<bool>("isSimulation",true);
    isSimulation = get_parameter("isSimulation").as_bool();
    base_frame = isSimulation? "base_footprint" : "laser";
    timer = create_wall_timer(200ms,[&](){control_cycle();});
    marker_pub = create_publisher<visualization_msgs::msg::Marker>("obstacle_marker",1); 

}

void Monitor::control_cycle(){
    geometry_msgs::msg::TransformStamped robot2obstacle;
    try{
        robot2obstacle = tf_buffer.lookupTransform(base_frame, "detected_obstacle", tf2::TimePointZero);
    }
    catch(tf2::TransformException& exception){
        RCLCPP_WARN(get_logger(),"Transform exception caught: %s", exception.what());
        return;
    }
    double x = robot2obstacle.transform.translation.x;
    double y = robot2obstacle.transform.translation.y;
    double z = robot2obstacle.transform.translation.z;
    double theta = std::atan2(y,x);

    geometry_msgs::msg::Point robot;
    robot.x = 0;
    robot.y = 0;
    robot.z = 0;
    geometry_msgs::msg::Point obstacle;
    obstacle.x = x;
    obstacle.y = y;
    obstacle.z = z;

    RCLCPP_INFO(this->get_logger(), "Nearest obstacle is at %.2lfi,%.2lfj,%.2lfdeg m", x,y,theta*180*M_1_PI);


    visualization_msgs::msg::Marker marker;
    marker.header.frame_id = base_frame;
    marker.header.stamp = now();
    marker.type = marker.ARROW;
    marker.action = marker.ADD;
    marker.lifetime = rclcpp::Duration(1s);
    marker.points = {robot,obstacle};
    marker.color.a = 1.0;
    marker.color.r = 1.0;
    marker.scale.x = 0.02;
    marker.scale.y = 0.1;
    marker.scale.z = 0.1;

    marker_pub->publish(marker);
    
}
