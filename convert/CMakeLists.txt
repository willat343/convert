cmake_minimum_required(VERSION 3.12) # 3.12 required for: add_compile_definitions
project(convert
    VERSION 0.3.4
    DESCRIPTION "Conversion Library"
    LANGUAGES CXX
)

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
        src/sensorbox_ros/pose_twist.cpp
        src/sensorbox_ros/pose.cpp
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

# Report components that will be built
message(NOTICE "Components:")
message(NOTICE "\t    EIGEN = ${BUILD_EIGEN_COMPONENTS}")
message(NOTICE "\t    GTSAM = ${BUILD_GTSAM_COMPONENTS}")
message(NOTICE "\t    MANIF = ${BUILD_MANIF_COMPONENTS}")
message(NOTICE "\t   MATLAB = ${BUILD_MATLAB_COMPONENTS}")
message(NOTICE "\t      ROS = ${BUILD_ROS_COMPONENTS}")
message(NOTICE "\tSENSORBOX = ${BUILD_SENSORBOX_COMPONENTS}")

# Template backtrace limit
set(TEMPLATE_BACKTRACE_LIMIT "10" CACHE STRING "Template backtrace limit for compilation error verbosity. 0 to disable." FORCE)

# Compile of library and tests
if (convert_SRC_FILES)
    message(DEBUG "Building convert library as lib${PROJECT_NAME}.so with\n\
        convert_SRC_FILES = ${convert_SRC_FILES}\n\
        convert_DEFINITIONS = ${convert_DEFINITIONS}\n\
        convert_SYSTEM_INCLUDE_DIRS = ${convert_SYSTEM_INCLUDE_DIRS}\n\
        convert_SYSTEM_LIBRARIES = ${convert_SYSTEM_LIBRARIES}")

    # Build library
    add_library(${PROJECT_NAME} SHARED
        ${convert_SRC_FILES}
    )

    # Link libraries
    target_link_libraries(${PROJECT_NAME} PUBLIC
        ${convert_SYSTEM_LIBRARIES}
    )

    # Definitions
    target_compile_definitions(${PROJECT_NAME} PUBLIC ${convert_DEFINITIONS})

    # Properties
    set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 20
    )

    # Compile options
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall -Wextra -Wpedantic -ftemplate-backtrace-limit=${TEMPLATE_BACKTRACE_LIMIT}
    )

    # Include directories
    target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )

    # System include directories
    target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC
        ${convert_SYSTEM_INCLUDE_DIRS}
    )

    # Build tests
    if(BUILD_TESTS)
        add_subdirectory(test)
    endif()

    # Configure package version and config files
    include(CMakePackageConfigHelpers)
    write_basic_package_version_file(
        "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
    )
    configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    )

    # Installation
    install(
        TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}"
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
    install(
        EXPORT ${PROJECT_NAME}
        DESTINATION ${PROJECT_NAME}
        FILE ${PROJECT_NAME}-export.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    )
    install(
        FILES
            "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    )
    install(
        DIRECTORY include/${PROJECT_NAME}
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        FILES_MATCHING
            PATTERN "*.hpp"
            PATTERN "*.h"
    )

    # Uninstallation
    if(NOT TARGET uninstall)
        configure_file(
            "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
            "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
            @ONLY
        )

        # Add uninstall target
        add_custom_target(uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
    endif()
else()
    message(WARNING "Not building convert library, possibly because no valid combination of components was enabled.")
endif()

# Build Documentation
if (BUILD_DOCUMENTATION)
    find_package(Doxygen REQUIRED)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    configure_file(Doxyfile.in ${DOXYGEN_OUT})
    add_custom_target(documentation ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating documentation with doxygen."
        VERBATIM
    )
endif()
