# CMakeLists.txt file to configure build of uaspire_msgs

# Set minimum version of CMake required to build
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

# Find ament meta build system
find_package(ament_cmake REQUIRED)

# Create uaspire_controls project
project(uaspire_msgs
    DESCRIPTION "UASPIRE Messages"
    LANGUAGES C CXX)

# Find required packages
find_package(rosidl_default_generators REQUIRED)

# Create targets and add target dependencies
rosidl_generate_interfaces(${PROJECT_NAME}
    "msg/Command.msg"
    "msg/Sensors.msg"
)

# Install files to correct locations

ament_export_dependencies(rosidl_default_runtime)
ament_package()
