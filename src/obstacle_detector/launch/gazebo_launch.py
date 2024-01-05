from launch import LaunchDescription
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch_ros.actions import Node
import os
from ament_index_python.packages import get_package_share_directory
from launch.launch_description_sources import PythonLaunchDescriptionSource

from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription(
      [
          
        Node(package = 'obstacle_detector',
             executable= 'Detector',
             output = 'screen',
             parameters=[{'use_sim_time' : True}, {'isSimulation' : True}],
             remappings=[('scan','scan_raw')]
        ),

        Node(package = 'rviz2',
             executable= 'rviz2',
              output = 'screen',
              parameters=[{'use_sim_time' : True}],
        ),

        IncludeLaunchDescription(
          PythonLaunchDescriptionSource(
            os.path.join(
                get_package_share_directory("my_bumpgo"),
                'launch',
                'MyBumpGo.launch.py'
            )                        
          )
        ),
      ]
    )
    