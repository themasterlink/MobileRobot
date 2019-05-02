cmake_minimum_required(VERSION 3.12)
project(mobile_robotic)

set(CMAKE_CXX_STANDARD 17)
set(OpenCV_DIR /usr/local/Cellar/opencv/HEAD-37cbcf0_4/share/OpenCV)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(mobile_robotic main.cpp src/Robot.cpp src/Robot.h src/Map.cpp src/Map.h src/BaseTypes.h src/Point2.h src/Visualizer.cpp src/Visualizer.h src/RobotController.cpp src/RobotController.h)
target_link_libraries( mobile_robotic ${OpenCV_LIBS} )
