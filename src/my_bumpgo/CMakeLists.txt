cmake_minimum_required(VERSION 3.8)
project(my_bumpgo)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)

set(dependencies
rclcpp
sensor_msgs
geometry_msgs
)

include_directories(include)

add_executable(bumpgo
  src/MyBumpGo.cpp
  src/main.cpp
)
ament_target_dependencies(bumpgo ${dependencies})




install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})

install(TARGETS
bumpgo
ARCHIVE DESTINATION lib
LIBRARY DESTINATION lib
RUNTIME DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
find_package(ament_lint_auto REQUIRED)
ament_lint_auto_find_test_dependencies()

set(ament_cmake_copyright_FOUND TRUE)
ament_lint_auto_find_test_dependencies()
endif()

ament_package()
