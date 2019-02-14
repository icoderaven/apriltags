# apriltags CMake files
# Humphrey Hu, 2014
# Originally by Michael Kaess
# Modified to be catkinized by Kumar Shaurya Shankar, 2016
cmake_minimum_required(VERSION 2.8.3)
project(apriltags)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Defaults to release build
if (NOT DEFINED CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
  message(STATUS "No build type selected, default to Release")
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif ()
message(STATUS "Build configuration: ${CMAKE_BUILD_TYPE}")

## Find catkin macros and libraries
find_package(catkin REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

## Add support for C++11, supported in ROS Kinetic and newer
add_definitions(-std=c++11)

###################################
## catkin specific configuration ##
###################################
catkin_package(
    INCLUDE_DIRS include ${EIGEN3_INCLUDE_DIR}
    LIBRARIES apriltags
    DEPENDS OpenCV
)


message(STATUS "OpenCV found at: ${OpenCV_INCLUDE_DIRS}")
if( OpenCV_VERSION VERSION_EQUAL "3")
	add_definitions("-DOPENCV3=1")
	list(APPEND apriltags_DEFS "-DOPENCV3=1")
endif()

# Camera drivers
# find_package(V4L2 REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -Wno-unused-parameter -Wno-unused-function -O3 -fno-strict-overflow")

###########
## Build ##
###########
include_directories(
    include
    ${OpenCV_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
)

file(GLOB LIBRARY_SRC
    "src/*.cc"
)

## Declare library
add_library(${PROJECT_NAME} SHARED ${LIBRARY_SRC}
)
## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES} ${OpenCV_LIBRARIES}
)

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

#############
## Install ##
#############

## Mark executables and/or libraries for installation
install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}
ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

## Mark header files for installation
install(DIRECTORY include/${PROJECT_NAME}/
DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)