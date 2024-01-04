cmake_minimum_required(VERSION 3.0.2)
project(go2_ros1_ws)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
SET(CMAKE_CXX_STANDARD 17)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

include_directories(/usr/local/include/ddscxx /usr/local/include/iceoryx/v2.0.2)
link_libraries(unitree_sdk2 ddsc ddscxx rt pthread)

catkin_package(

)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(go2_ros1_node src/sub_pub_cmd.cpp)
target_link_libraries(go2_ros1_node ${catkin_LIBRARIES})