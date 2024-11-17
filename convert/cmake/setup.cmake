# CMake Build Type
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRel" )
endif()
message(STATUS "Build type set to ${CMAKE_BUILD_TYPE}")

# General Options
option(BUILD_DOCUMENTATION "Build Doxygen Documentation" OFF)
option(BUILD_TESTS "Build Tests" OFF)

# Find packages quietly to set defaults
find_package(Eigen3 3.3 QUIET)
find_package(GTSAM QUIET)
find_package(manif QUIET)
find_package(Matlab QUIET)
find_package(geometry_msgs QUIET)
find_package(sensorbox QUIET)

# Component Options
option(BUILD_EIGEN_COMPONENTS "Build Eigen Components" ${Eigen3_FOUND})
option(BUILD_GTSAM_COMPONENTS "Build GTSAM Components" ${GTSAM_FOUND})
option(BUILD_MANIF_COMPONENTS "Build manif Components" ${manif_FOUND})
option(BUILD_MATLAB_COMPONENTS "Build MATLAB Components" ${Matlab_FOUND})
option(BUILD_ROS_COMPONENTS "Build ROS Components" ${geometry_msgs_FOUND})
option(BUILD_SENSORBOX_COMPONENTS "Build sensorbox Components" ${sensorbox_FOUND})

# Enforce component dependencies (internal to convert, not external library dependencies)
if (BUILD_MANIF_COMPONENTS AND NOT BUILD_EIGEN_COMPONENTS)
    message(WARNING "BUILD_MANIF_COMPONENTS was enabled but it relies on BUILD_EIGEN_COMPONENTS which \
            was not enabled. Turning on BUILD_EIGEN_COMPONENTS.")
    set(BUILD_EIGEN_COMPONENTS ON CACHE BOOL "Build manif Components of Convert Library" FORCE)
endif()

# Find required packages for enabled components
if (BUILD_EIGEN_COMPONENTS AND (NOT DEFINED Eigen3_FOUND OR NOT ${Eigen3_FOUND}))
    find_package(Eigen3 3.3 REQUIRED)
endif()
if (BUILD_GTSAM_COMPONENTS AND (NOT DEFINED GTSAM_FOUND OR NOT ${GTSAM_FOUND}))
    find_package(GTSAM REQUIRED)
endif()
if (BUILD_MANIF_COMPONENTS AND (NOT DEFINED manif_FOUND OR NOT ${manif_FOUND}))
    find_package(manif REQUIRED)
endif()
if (BUILD_MATLAB_COMPONENTS AND (NOT DEFINED Matlab_FOUND OR NOT ${Matlab_FOUND}))
    find_package(Matlab REQUIRED MEX_COMPILER)
endif()
if (BUILD_ROS_COMPONENTS)
    if (NOT DEFINED geometry_msgs_FOUND OR NOT ${geometry_msgs_FOUND})
        find_package(geometry_msgs REQUIRED)
    endif()
    if (NOT DEFINED nav_msgs_FOUND OR NOT ${nav_msgs_FOUND})
        find_package(nav_msgs REQUIRED)
    endif()
    if (NOT DEFINED sensor_msgs_FOUND OR NOT ${sensor_msgs_FOUND})
        find_package(sensor_msgs REQUIRED)
    endif()
    if (NOT DEFINED std_msgs_FOUND OR NOT ${std_msgs_FOUND})
        find_package(std_msgs REQUIRED)
    endif()
endif()
if (BUILD_SENSORBOX_COMPONENTS AND (NOT DEFINED sensorbox_FOUND OR NOT ${sensorbox_FOUND}))
    find_package(sensorbox REQUIRED)
endif()

# Variables
set(convert_SRC_FILES "")
set(convert_DEFINITIONS "")
set(convert_SYSTEM_INCLUDE_DIRS "")
set(convert_SYSTEM_LIBRARIES "")

# Process components in dependency order so that convert_SYSTEM_LIBRARIES order has most dependent libraries first. The
# external library dependencies are:
#   manif -> Eigen (header-only)
#   gtsam -> Eigen (header-only)
#   sensorbox -> mathbox (header-only), Eigen (header-only)

if (BUILD_MANIF_COMPONENTS AND BUILD_ROS_COMPONENTS)
    # Append to source files
    list(APPEND convert_SRC_FILES
        src/manif_ros/geometry_msgs.cpp
    )

    # Append to definitions
    list(APPEND convert_DEFINITIONS CONVERT_MANIF CONVERT_ROS)

    # Append to system include directories
    list(APPEND convert_SYSTEM_INCLUDE_DIRS
        ${manif_INCLUDE_DIRS}
        ${geometry_msgs_INCLUDE_DIRS}
    )

    # Append to system libraries
    list(APPEND convert_SYSTEM_LIBRARIES
        ${geometry_msgs_LIBRARIES}
    )
endif()

if (BUILD_GTSAM_COMPONENTS AND BUILD_ROS_COMPONENTS)
    # Append to source files
    list(APPEND convert_SRC_FILES
        src/gtsam_ros/geometry_geometry_msgs.cpp
        src/gtsam_ros/navigation_nav_msgs.cpp
    )

    # Append to definitions
    list(APPEND convert_DEFINITIONS CONVERT_GTSAM CONVERT_ROS)

    # Append to system include directories
    list(APPEND convert_SYSTEM_INCLUDE_DIRS
        ${GTSAM_INCLUDE_DIR}
        ${geometry_msgs_INCLUDE_DIRS}
        ${nav_msgs_INCLUDE_DIRS}
    )

    # Append to system libraries
    list(APPEND convert_SYSTEM_LIBRARIES
        gtsam
        ${geometry_msgs_LIBRARIES}
        ${nav_msgs_LIBRARIES}
    )
endif()

if (BUILD_SENSORBOX_COMPONENTS AND BUILD_ROS_COMPONENTS)
    # Append to source files
    list(APPEND convert_SRC_FILES
        src/sensorbox_ros/imu.cpp
    )

    # Append to definitions
    list(APPEND convert_DEFINITIONS CONVERT_ROS CONVERT_SENSORBOX)

    # Append to system include directories
    list(APPEND convert_SYSTEM_INCLUDE_DIRS
        ${sensor_msgs_INCLUDE_DIRS}
    )

    # Append to system libraries
    list(APPEND convert_SYSTEM_LIBRARIES
        sensorbox
        ${sensor_msgs_LIBRARIES}
    )
endif()

if (BUILD_EIGEN_COMPONENTS AND BUILD_GTSAM_COMPONENTS)
    # Append to source files
    list(APPEND convert_SRC_FILES
        src/eigen_gtsam/geometry.cpp
        src/eigen_gtsam/navigation.cpp
    )

    # Append to definitions
    list(APPEND convert_DEFINITIONS CONVERT_EIGEN CONVERT_GTSAM)

    # Append to system include directories
    list(APPEND convert_SYSTEM_INCLUDE_DIRS
        ${EIGEN3_INCLUDE_DIRS}
        ${GTSAM_INCLUDE_DIR}
    )

    # Append to system libraries
    list(APPEND convert_SYSTEM_LIBRARIES
        gtsam
        Eigen3::Eigen
    )
endif()

if (BUILD_ROS_COMPONENTS)
    # Append to source files
    list(APPEND convert_SRC_FILES
        src/ros/geometry_msgs_nav_msgs.cpp
        src/ros/nav_msgs.cpp
    )

    # Append to definitions
    list(APPEND convert_DEFINITIONS CONVERT_ROS)

    # Append to system include directories
    list(APPEND convert_SYSTEM_INCLUDE_DIRS
        ${geometry_msgs_INCLUDE_DIRS}
        ${nav_msgs_INCLUDE_DIRS}
        ${std_msgs_INCLUDE_DIRS}
    )

    # Append to system libraries
    list(APPEND convert_SYSTEM_LIBRARIES
        ${nav_msgs_LIBRARIES}
        ${geometry_msgs_LIBRARIES}
        ${std_msgs_LIBRARIES}
    )

    if (BUILD_EIGEN_COMPONENTS)
        # Append to source files
        list(APPEND convert_SRC_FILES
            src/eigen_ros/geometry_msgs.cpp
        )

        # Append to definitions
        list(APPEND convert_DEFINITIONS CONVERT_EIGEN)

        # Append to system include directories
        list(APPEND convert_SYSTEM_INCLUDE_DIRS
            ${EIGEN3_INCLUDE_DIRS}
        )

        # Append to system libraries
        list(APPEND convert_SYSTEM_LIBRARIES
            Eigen3::Eigen
        )
    endif()
endif()

if (BUILD_MATLAB_COMPONENTS)
    # Append to system include directories
    list(APPEND convert_SYSTEM_INCLUDE_DIRS
        ${Matlab_INCLUDE_DIRS}
    )

    # Append to definitions
    list(APPEND convert_DEFINITIONS CONVERT_MATLAB)

    if (BUILD_EIGEN_COMPONENTS)
        # Append to definitions
        list(APPEND convert_DEFINITIONS CONVERT_EIGEN)

        # Append to system include directories
        list(APPEND convert_SYSTEM_INCLUDE_DIRS
            ${EIGEN3_INCLUDE_DIRS}
        )

        # Append to system libraries
        list(APPEND convert_SYSTEM_LIBRARIES
            Eigen3::Eigen
        )
    endif()
endif()

if (BUILD_EIGEN_COMPONENTS)
    # Append to definitions
    list(APPEND convert_DEFINITIONS CONVERT_EIGEN)

    # Append to system include directories
    list(APPEND convert_SYSTEM_INCLUDE_DIRS
        ${EIGEN3_INCLUDE_DIRS}
    )

    # Append to system libraries
    list(APPEND convert_SYSTEM_LIBRARIES
        Eigen3::Eigen
    )
endif()

# Remove duplicates (first occurrence is preserved)
list(REMOVE_DUPLICATES convert_DEFINITIONS)
list(REMOVE_DUPLICATES convert_SYSTEM_INCLUDE_DIRS)
list(REMOVE_DUPLICATES convert_SYSTEM_LIBRARIES)

# Installation directories
include(GNUInstallDirs)
