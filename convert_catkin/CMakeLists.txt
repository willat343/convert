cmake_minimum_required(VERSION 3.5)
project(convert_catkin
    VERSION 0.3.1
    DESCRIPTION "convert catkin"
    LANGUAGES CXX
)

# Find catkin (which adds to CMAKE_PREFIX_PATH)
find_package(catkin REQUIRED)

# Setup
include(${CMAKE_CURRENT_SOURCE_DIR}/../convert/cmake/setup.cmake)

# Install convert
include(ExternalProject)
file(MAKE_DIRECTORY ${CATKIN_DEVEL_PREFIX}/include)
string(REPLACE ";" "|" CMAKE_PREFIX_PATH_EXT_PROJ "${CMAKE_PREFIX_PATH}")
ExternalProject_Add(convert
    PREFIX ${CMAKE_BINARY_DIR}
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../convert
    INSTALL_DIR ${CATKIN_DEVEL_PREFIX}
    BUILD_ALWAYS TRUE
    LIST_SEPARATOR | # Use alternate list separator to pass lists to CMAKE_ARGS
    CMAKE_ARGS
        -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH_EXT_PROJ}
        -DCMAKE_INSTALL_PREFIX=${CATKIN_DEVEL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DBUILD_DOCUMENTATION=${BUILD_DOCUMENTATION}
        -DBUILD_TESTS=${BUILD_TESTS}
        -DBUILD_EIGEN_COMPONENTS=${BUILD_EIGEN_COMPONENTS}
        -DBUILD_GTSAM_COMPONENTS=${BUILD_GTSAM_COMPONENTS}
        -DBUILD_MANIF_COMPONENTS=${BUILD_MANIF_COMPONENTS}
        -DBUILD_MATLAB_COMPONENTS=${BUILD_MATLAB_COMPONENTS}
        -DBUILD_ROS_COMPONENTS=${BUILD_ROS_COMPONENTS}
        -DBUILD_SENSORBOX_COMPONENTS=${BUILD_SENSORBOX_COMPONENTS}
)

# Configure cfg_extras.cmake
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/cfg_extras.cmake.in cfg_extras.cmake @ONLY)

# Catkin package
catkin_package(
    INCLUDE_DIRS
        ${CATKIN_DEVEL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}
        ${convert_SYSTEM_INCLUDE_DIRS}
    LIBRARIES
        ${CATKIN_DEVEL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/libconvert.so
        ${convert_SYSTEM_LIBRARIES}
    CFG_EXTRAS
        ${CMAKE_BINARY_DIR}/cfg_extras.cmake
)
