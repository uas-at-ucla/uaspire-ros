# CMakeLists.txt file to configure build of uaspire_controls

# Set minimum version of CMake required to build
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

# Find ament meta build system
find_package(ament_cmake REQUIRED)

# Create uaspire_controls project
project(uaspire_controls
    DESCRIPTION "UASPIRE Controls"
    LANGUAGES CXX)

# Setup C++ version and compiler flags
if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "(GNU|AppleClang|Clang)")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find required packages
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(uaspire_msgs REQUIRED)

# Create targets and add target dependencies
add_executable(uaspire_controls
    main.cc
)
ament_target_dependencies(uaspire_controls
    rclcpp
    std_msgs
    uaspire_msgs
)

# Install files to correct locations
install(TARGETS uaspire_controls
    DESTINATION bin)

ament_package()
