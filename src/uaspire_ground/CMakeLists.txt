# CMakeLists.txt file to configure build of uaspire_ground

# Set minimum version of CMake required to build
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Find ament meta build system
find_package(ament_cmake REQUIRED)

# Create uaspire_ground project
project(uaspire_ground
    DESCRIPTION "UASPIRE Ground"
    LANGUAGES)

# Find required packages
find_package(uaspire_msgs REQUIRED)
find_package(Node REQUIRED)
find_package(Npm REQUIRED)

# Create targets and add target dependencies
add_custom_target(build_ground ALL
    COMMENT "Build ground station"
    COMMAND ${NPM_EXECUTABLE} install
    USES_TERMINAL
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

# Install files to correct locations
install(CODE "
execute_process(
    COMMAND ${NPM_EXECUTABLE} install --prefix=${CMAKE_INSTALL_PREFIX} -g
    RESULT_VARIABLE install_result
    WORKING_DIRECTORY \"${CMAKE_SOURCE_DIR}\"
)
if (NOT install_result EQUAL 0)
    message(FATAL_ERROR \"Error installing to prefix\")
endif()
")

ament_package()
