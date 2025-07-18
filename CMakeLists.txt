cmake_minimum_required(VERSION 3.12) # 3.12 required for: add_compile_definitions
project(convert
    VERSION 0.4.0
    DESCRIPTION "Conversion Library"
    LANGUAGES CXX
)

# Installation directories
include(GNUInstallDirs)

# CMake Build Type
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRel" )
endif()
message(STATUS "Build type set to ${CMAKE_BUILD_TYPE}")

# General Options
option(BUILD_DOCUMENTATION "Build Doxygen Documentation" OFF)
option(BUILD_TESTS "Build Tests" OFF)
option(DEVELOPER_MODE "Use local versions of sensorbox" OFF)
option(USE_SYSTEM_Eigen3 "Use system install of Eigen3" ON)
option(USE_SYSTEM_manif "Use system install of manif" ON)

# Get information about the CXX Compiler
message(STATUS "Detected ${CMAKE_CXX_COMPILER_ID} CXX compiler version ${CMAKE_CXX_COMPILER_VERSION}")

# Get CXX compiler version
string(REPLACE "." ";" CMAKE_CXX_COMPILER_VERSION_LIST ${CMAKE_CXX_COMPILER_VERSION})
list(GET CMAKE_CXX_COMPILER_VERSION_LIST 0 CMAKE_CXX_COMPILER_VERSION_MAJOR)
list(GET CMAKE_CXX_COMPILER_VERSION_LIST 1 CMAKE_CXX_COMPILER_VERSION_MINOR)

# Optional Dependency: Eigen3 (Target: Eigen3::Eigen, Note: Eigen3::Eigen sets INTERFACE_INCLUDE_DIRECTORIES)
if (TARGET Eigen3::Eigen)
    option(BUILD_EIGEN_COMPONENTS "Build Eigen Components" ON)
else()
    set(EIGEN3_VERSION "3.3.7")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU") # Note: gcc/g++
        if (CMAKE_CXX_COMPILER_VERSION_MAJOR GREATER_EQUAL 10)
            # g++-10 with c++20 requires Eigen3 >=3.3.9. For further details see issues:
            #  - https://gitlab.com/libeigen/eigen/-/issues/2012
            #  - https://gitlab.com/libeigen/eigen/-/issues/1872
            set(EIGEN3_VERSION "3.3.9")
        endif()
    endif()
    if (${USE_SYSTEM_Eigen3})
        find_package(Eigen3 ${EIGEN3_VERSION} QUIET)
        option(BUILD_EIGEN_COMPONENTS "Build Eigen Components" ${Eigen3_FOUND})
        if (BUILD_EIGEN_COMPONENTS AND (NOT DEFINED Eigen3_FOUND OR NOT ${Eigen3_FOUND}))
            find_package(Eigen3 ${EIGEN3_VERSION} REQUIRED)
        endif()
    else()
        FetchContent_Declare(
            eigen
            GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
            GIT_TAG ${EIGEN3_VERSION}
        )
        FetchContent_MakeAvailable(eigen)
        message(STATUS "Fetched eigen to ${eigen_SOURCE_DIR} with version ${EIGEN3_VERSION}")
    endif()
endif()

# Optional Dependency: manif (Target: MANIF::manif, Note: MANIF::manif sets INTERFACE_INCLUDE_DIRECTORIES, and
# manif_LIBRARIES is empty)
if (TARGET MANIF::manif)
    option(BUILD_MANIF_COMPONENTS "Build manif Components" ON)
else()
    set(MANIF_VERSION "0.0.5")
    if (${USE_SYSTEM_manif})
        find_package(manif ${MANIF_VERSION} QUIET)
        option(BUILD_MANIF_COMPONENTS "Build manif Components" ${manif_FOUND})
        if (BUILD_MANIF_COMPONENTS AND (NOT DEFINED manif_FOUND OR NOT ${manif_FOUND}))
            find_package(manif ${MANIF_VERSION} REQUIRED)
        endif()
    else()
        FetchContent_Declare(
            manif
            GIT_REPOSITORY https://github.com/artivis/manif.git
            GIT_TAG ${MANIF_VERSION}
        )
        FetchContent_MakeAvailable(manif)
        message(STATUS "Fetched manif to ${manif_SOURCE_DIR} with version ${MANIF_VERSION}")
    endif()
endif()
# Enforce component dependencies (internal to convert, not external library dependencies)
if (BUILD_MANIF_COMPONENTS AND NOT BUILD_EIGEN_COMPONENTS)
    message(ERROR "BUILD_MANIF_COMPONENTS was enabled but it relies on BUILD_EIGEN_COMPONENTS which \
            was not enabled (either disabled or Eigen3 was not found).")
endif()

# Optional Dependency: GTSAM
if (TARGET gtsam)
    option(BUILD_GTSAM_COMPONENTS "Build GTSAM Components" ON)
else()
    set(GTSAM_VERSION "")
    find_package(GTSAM ${GTSAM_VERSION} QUIET)
    option(BUILD_GTSAM_COMPONENTS "Build GTSAM Components" ${GTSAM_FOUND})
    if (BUILD_GTSAM_COMPONENTS AND (NOT DEFINED GTSAM_FOUND OR NOT ${GTSAM_FOUND}))
        find_package(GTSAM ${GTSAM_VERSION} REQUIRED)
    endif()
endif()

# Optional Dependency: Matlab
if (TARGET Matlab::matlab)
    option(BUILD_MATLAB_COMPONENTS "Build MATLAB Components" ON)
else()
    set(MATLAB_VERSION "")
    find_package(Matlab ${MATLAB_VERSION} QUIET)
    option(BUILD_MATLAB_COMPONENTS "Build MATLAB Components" ${Matlab_FOUND})
    if (BUILD_MATLAB_COMPONENTS AND (NOT DEFINED Matlab_FOUND OR NOT ${Matlab_FOUND}))
        find_package(Matlab ${MATLAB_VERSION} REQUIRED MEX_COMPILER)
    endif()
endif()

# Optional Dependency: ROS 1
find_package(geometry_msgs QUIET)
find_package(nav_msgs QUIET)
find_package(sensor_msgs QUIET)
find_package(std_msgs QUIET)
option(BUILD_ROS_COMPONENTS "Build ROS Components" ${geometry_msgs_FOUND})
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

# Optional Dependency: sensorbox (Target: sensorbox::sensorbox)
if (TARGET sensorbox::sensorbox)
    option(BUILD_SENSORBOX_COMPONENTS "Build sensorbox Components" ON)
else()
    option(BUILD_SENSORBOX_COMPONENTS "Build sensorbox Components" ON)
    if (${BUILD_SENSORBOX_COMPONENTS})
        set(SENSORBOX_VERSION "0.5.0")
        FetchContent_Declare(
            sensorbox
            GIT_REPOSITORY git@github.com:willat343/sensorbox.git
            GIT_TAG v${SENSORBOX_VERSION}
        )
        FetchContent_MakeAvailable(sensorbox)
        if (${DEVELOPER_MODE})
            message(STATUS "Found sensorbox at ${sensorbox_SOURCE_DIR} (DEVELOPER_MODE = ON)")
        else()
            message(STATUS "Fetched sensorbox to ${sensorbox_SOURCE_DIR} with version ${SENSORBOX_VERSION}")
        endif()
    endif()
endif()

# Variables
set(convert_SRC_FILES "")
set(convert_DEFINITIONS "")
set(convert_SYSTEM_INCLUDE_DIRS "")
set(convert_SYSTEM_LIBRARIES "")

# Process components in dependency order so that convert_SYSTEM_LIBRARIES order has most dependent libraries first.
# Header-only libraries can be flexible in their ordering.
# The external library dependencies are:
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
        ${geometry_msgs_INCLUDE_DIRS}
    )

    # Append to system libraries
    list(APPEND convert_SYSTEM_LIBRARIES
        MANIF::manif
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

    # Append to system libraries
    list(APPEND convert_SYSTEM_LIBRARIES
        Eigen3::Eigen
        gtsam
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

        # Append to system libraries
        list(APPEND convert_SYSTEM_LIBRARIES
            Eigen3::Eigen
        )
    endif()
endif()

if (BUILD_EIGEN_COMPONENTS)
    # Append to definitions
    list(APPEND convert_DEFINITIONS CONVERT_EIGEN)

    # Append to system libraries
    list(APPEND convert_SYSTEM_LIBRARIES
        Eigen3::Eigen
    )
endif()

# Remove duplicates (first occurrence is preserved)
list(REMOVE_DUPLICATES convert_DEFINITIONS)
list(REMOVE_DUPLICATES convert_SYSTEM_INCLUDE_DIRS)
list(REMOVE_DUPLICATES convert_SYSTEM_LIBRARIES)

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
    set(LIBRARY_NAME ${PROJECT_NAME})
    add_library(${LIBRARY_NAME} SHARED
        ${convert_SRC_FILES}
    )
    add_library(${PROJECT_NAME}::${LIBRARY_NAME} ALIAS ${LIBRARY_NAME})

    # Definitions
    target_compile_definitions(${LIBRARY_NAME} PUBLIC ${convert_DEFINITIONS})

    # Properties
    set_target_properties(${LIBRARY_NAME} PROPERTIES
        CXX_STANDARD 20
    )

    # Compile options
    target_compile_options(${LIBRARY_NAME} PRIVATE
        -Wall -Wextra -Wpedantic -ftemplate-backtrace-limit=${TEMPLATE_BACKTRACE_LIMIT}
    )

    # Include directories
    target_include_directories(${LIBRARY_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )

    # System include directories
    target_include_directories(${LIBRARY_NAME} SYSTEM PUBLIC
        ${convert_SYSTEM_INCLUDE_DIRS}
    )

    # Link libraries
    target_link_libraries(${LIBRARY_NAME} PUBLIC
        ${convert_SYSTEM_LIBRARIES}
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
        TARGETS ${LIBRARY_NAME}
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
