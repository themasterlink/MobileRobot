cmake_minimum_required(VERSION 3.12)
project(mobile_robotic)

set(CMAKE_CXX_STANDARD 17)
set(OpenCV_DIR /usr/local/Cellar/opencv/HEAD-37cbcf0_4/share/OpenCV)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(mobile_robotic main.cpp Robot.cpp Robot.h Map.cpp Map.h BaseTypes.h Point2.h Visualizer.cpp Visualizer.h RobotController.cpp RobotController.h)
target_link_libraries( mobile_robotic ${OpenCV_LIBS} )