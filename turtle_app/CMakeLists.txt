cmake_minimum_required(VERSION 3.0.2)
project(turtle_app)

add_compile_options(-std=c++17)

find_package(catkin REQUIRED
  roscpp
  actionlib
  move_base_msgs
  tf2_ros
  image_transport
  cv_bridge
  sensor_msgs
  message_generation
)

find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED)

add_service_files(
  FILES
  CameraCapture.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
  sensor_msgs
)

###################################
## catkin specific configuration ##
###################################
catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS
  roscpp
  actionlib
  move_base_msgs
  tf2_ros
  image_transport
  cv_bridge
  sensor_msgs
  message_runtime
  DEPENDS Boost
)

###########
## Build ##
###########

## Specify additional locations of header files
include_directories(
	include
	${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(${PROJECT_NAME}
  src/fsm/FiniteStateMachine.cpp
  src/states/Navigate.cpp
  src/states/CameraCapture.cpp
  src/states/Initialize.cpp
  src/states/Idle.cpp
  src/states/Terminate.cpp
  src/world_model.cpp
)

add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(
  ${PROJECT_NAME}
  ${OpenCV_LIBRARIES}
  ${Boost_LIBRARIES}
)

add_executable(${PROJECT_NAME}_node src/turtle_node.cpp)
add_executable(${PROJECT_NAME}_camera_server src/camera_server.cpp)

set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME turtle_node PREFIX "")
set_target_properties(${PROJECT_NAME}_camera_server PROPERTIES OUTPUT_NAME camera_server PREFIX "")

## Add cmake target dependencies of the executable
add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(${PROJECT_NAME}_camera_server ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}_node
	${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME}_camera_server
  ${PROJECT_NAME}
  ${catkin_LIBRARIES}
)
