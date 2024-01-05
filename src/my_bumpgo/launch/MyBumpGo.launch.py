from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch_ros.actions import Node
import os
from ament_index_python.packages import get_package_share_directory
from launch.launch_description_sources import PythonLaunchDescriptionSource

def generate_launch_description():


    bumpgo_cmd = Node(package='my_bumpgo',
                      executable='bumpgo',
                      output='screen',
                      parameters=[{'use_sim_time': True }],
                      remappings=[
                        ('input_scan', 'scan_raw'),
                        ('output_vel', 'nav_vel')
                      ]
                )
    
    Simulation = IncludeLaunchDescription(
                  PythonLaunchDescriptionSource(
                    os.path.join(
                        get_package_share_directory("br2_tiago"),
                        'launch',
                        'sim.launch.py'
                    )                        
                  )
                )

    ld = LaunchDescription()
    ld.add_action(bumpgo_cmd)
    ld.add_action(Simulation)


    return ld
