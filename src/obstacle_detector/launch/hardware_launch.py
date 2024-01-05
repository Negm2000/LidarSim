from launch import LaunchDescription
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch_ros.actions import Node
import os
from ament_index_python.packages import get_package_share_directory
from launch.launch_description_sources import PythonLaunchDescriptionSource

from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(package = 'obstacle_detector',
             executable= 'Detector',
             output = 'screen',
             parameters=[{'use_sim_time' : False}, {'isSimulation' : False}],
        ),
        IncludeLaunchDescription(
          PythonLaunchDescriptionSource(
              os.path.join(
                  get_package_share_directory("rplidar_ros"),
                  'launch',
                  'view_rplidar_a1_launch.py'
              )                        
            )
          )
      ]
    )
    