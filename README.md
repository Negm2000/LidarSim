# ROS 2 LiDAR exercises in C++

Small ROS 2 (Humble) C++ packages I wrote while working through *A Concise Introduction to Robot Programming with ROS 2*, run in Gazebo on the simulated TIAGo robot and on a real RPLIDAR A1.

## Packages

- **`obstacle_detector`**: two nodes.
  - `Detector` subscribes to `/scan`, finds the nearest return and publishes it as a TF frame called `detected_obstacle`.
  - `Monitor` looks that frame up through TF every 200 ms, logs the obstacle's position and bearing, and publishes an arrow marker from the robot to the obstacle for RViz.
  - `gazebo_launch.py` runs it in simulation; `hardware_launch.py` runs it with the `rplidar_ros` driver. A parameter switches the base frame between the two.
- **`my_bumpgo`**: a finite-state machine (forward, back, turn) driven by the laser scan. The robot drives until something is within range in a 40 degree cone ahead, backs up, then turns toward open space.
- **`br2_tiago`**: launch files for the TIAGo simulation, taken from the book's repository.

## Build

```bash
colcon build --symlink-install
source install/setup.bash
ros2 launch obstacle_detector gazebo_launch.py
```
