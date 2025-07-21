cmake_minimum_required(VERSION 3.21)
project(convert
    VERSION 0.5.0
    DESCRIPTION "Conversion Library"
    LANGUAGES CXX
)

## Include Standard CMake Packages
# GNUInstallDirs for Install directories
include(GNUInstallDirs)
# FetchContent for dependencies
include(FetchContent)
# CTest for BUILD_TESTING option (default ON)
include(CTest)
# Package version and config file generation
include(CMakePackageConfigHelpers)

# General Options
option(BUILD_EIGEN_COMPONENTS "Build Eigen Components" OFF)
option(BUILD_MANIF_COMPONENTS "Build manif Components" OFF)
option(BUILD_GTSAM_COMPONENTS "Build GTSAM Components" OFF)
option(BUILD_MATLAB_COMPONENTS "Build MATLAB Components" OFF)
option(BUILD_ROS_COMPONENTS "Build ROS Components" OFF)
option(BUILD_SENSORBOX_COMPONENTS "Build sensorbox Components" OFF)
option(BUILD_DOCUMENTATION "Build Doxygen Documentation" OFF)
option(DEVELOPER_MODE "Use local versions of sensorbox" OFF)

# Enforce component dependencies (internal to convert, not external library dependencies)
if (BUILD_MANIF_COMPONENTS AND NOT BUILD_EIGEN_COMPONENTS)
    message(ERROR "BUILD_MANIF_COMPONENTS was enabled but it relies on BUILD_EIGEN_COMPONENTS which \
            was not enabled (either disabled or Eigen3 was not found).")
endif()

# Dependency: cmakebox
set(CMAKEBOX_VERSION "0.0.1")
FetchContent_Declare(
    cmakebox
    GIT_REPOSITORY git@github.com:willat343/cmakebox.git
    GIT_TAG v${CMAKEBOX_VERSION}
)
FetchContent_MakeAvailable(cmakebox)
list(APPEND CMAKE_MODULE_PATH "${cmakebox_SOURCE_DIR}/cmake")
include(CMakeBox)
include(Dependencies/Eigen3)
include(Dependencies/manif)

# CMake Build Type
setup_build_type()

# Get CXX Compiler Information
get_cxx_compiler_info()

# Optional Dependency: Eigen3 (Target: Eigen3::Eigen)
if (BUILD_EIGEN_COMPONENTS)
    set(EIGEN3_VERSION "3.4.0")
    import_Eigen3(
        VERSION ${EIGEN3_VERSION}
    )
endif()

# Optional Dependency: manif (Target: MANIF::manif)
if (BUILD_MANIF_COMPONENTS)
    set(MANIF_VERSION "0.0.6")
    import_manif(
        VERSION ${MANIF_VERSION}
    )
endif()

# Optional Dependency: GTSAM
if (BUILD_GTSAM_COMPONENTS AND NOT TARGET gtsam)
    set(GTSAM_VERSION "")
    find_package(GTSAM ${GTSAM_VERSION} REQUIRED)
    message(STATUS "Found GTSAM at ${GTSAM_DIR} with version ${GTSAM_VERSION}")
endif()

# Optional Dependency: Matlab
if (BUILD_MATLAB_COMPONENTS AND NOT TARGET Matlab::matlab)
    set(MATLAB_VERSION "")
    find_package(Matlab ${MATLAB_VERSION} REQUIRED MEX_COMPILER)
endif()

# Optional Dependency: ROS 1
if (BUILD_ROS_COMPONENTS)
    find_package(geometry_msgs REQUIRED)
    find_package(nav_msgs REQUIRED)
    find_package(sensor_msgs REQUIRED)
    find_package(std_msgs REQUIRED)
endif()

# Optional Dependency: sensorbox (Target: sensorbox::sensorbox)
if (BUILD_SENSORBOX_COMPONENTS)
    set(SENSORBOX_VERSION "0.6.0")
    import_dependency(
        sensorbox
        TARGET sensorbox::sensorbox
        VERSION ${SENSORBOX_VERSION}
        USE_SYSTEM_REQUIRED_VERSION ${SENSORBOX_VERSION}
        GIT_REPOSITORY git@github.com:willat343/sensorbox.git
        GIT_TAG v${SENSORBOX_VERSION}
    )
endif()

# Get number of components to build
SET(NUM_BUILD_COMPONENTS 0)
foreach(BUILD_COMPONENT
    BUILD_EIGEN_COMPONENTS
    BUILD_MANIF_COMPONENTS
    BUILD_GTSAM_COMPONENTS
    BUILD_MATLAB_COMPONENTS
    BUILD_ROS_COMPONENTS
    BUILD_SENSORBOX_COMPONENTS)
    if (${BUILD_COMPONENT})
        math(EXPR NUM_BUILD_COMPONENTS "${NUM_BUILD_COMPONENTS} + 1")
    endif()
endforeach()

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
message(NOTICE "Components (${NUM_BUILD_COMPONENTS} ENABLED):")
message(NOTICE "\t    EIGEN = ${BUILD_EIGEN_COMPONENTS}")
message(NOTICE "\t    GTSAM = ${BUILD_GTSAM_COMPONENTS}")
message(NOTICE "\t    MANIF = ${BUILD_MANIF_COMPONENTS}")
message(NOTICE "\t   MATLAB = ${BUILD_MATLAB_COMPONENTS}")
message(NOTICE "\t      ROS = ${BUILD_ROS_COMPONENTS}")
message(NOTICE "\tSENSORBOX = ${BUILD_SENSORBOX_COMPONENTS}")

# Template backtrace limit
set(TEMPLATE_BACKTRACE_LIMIT "10" CACHE STRING "Template backtrace limit for compilation error verbosity. 0 to disable." FORCE)

# Compile of library and tests
if (NUM_BUILD_COMPONENTS GREATER 0)
    # Build Library
    set(LIBRARY_NAME ${PROJECT_NAME})
    if (convert_SRC_FILES)
        # Build shared library
        add_library(${LIBRARY_NAME} SHARED
            ${convert_SRC_FILES}
        )
        set(SCOPE PUBLIC)
    else()
        # Build interface library
        add_library(${LIBRARY_NAME} INTERFACE)
        set(SCOPE INTERFACE)
    endif()
    add_library(${PROJECT_NAME}::${LIBRARY_NAME} ALIAS ${LIBRARY_NAME})
    message(DEBUG "Building ${PROJECT_NAME}::${LIBRARY_NAME} library with\n\
        convert_SRC_FILES = ${convert_SRC_FILES}\n\
        convert_DEFINITIONS = ${convert_DEFINITIONS}\n\
        convert_SYSTEM_INCLUDE_DIRS = ${convert_SYSTEM_INCLUDE_DIRS}\n\
        convert_SYSTEM_LIBRARIES = ${convert_SYSTEM_LIBRARIES}")

    # Definitions
    target_compile_definitions(${LIBRARY_NAME} ${SCOPE} ${convert_DEFINITIONS})

    # Properties
    set_target_properties(${LIBRARY_NAME} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
    )

    # Compile options
    if (convert_SRC_FILES)
        target_compile_options(${LIBRARY_NAME} PRIVATE
            -Wall -Wextra -Wpedantic -ftemplate-backtrace-limit=${TEMPLATE_BACKTRACE_LIMIT}
        )
    endif()

    # Include directories
    target_include_directories(${LIBRARY_NAME} ${SCOPE}
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )

    # System include directories
    target_include_directories(${LIBRARY_NAME} SYSTEM ${SCOPE}
        ${convert_SYSTEM_INCLUDE_DIRS}
    )

    # Link libraries
    target_link_libraries(${LIBRARY_NAME} ${SCOPE}
        ${convert_SYSTEM_LIBRARIES}
    )

    # Build tests
    if(BUILD_TESTS)
        add_subdirectory(test)
    endif()

    # Configure package version and config files
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
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
        NAMESPACE ${PROJECT_NAME}::
        FILE ${PROJECT_NAME}-export.cmake
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

    # Build-Tree Export
    export(
        EXPORT ${PROJECT_NAME}
        NAMESPACE ${PROJECT_NAME}::
        FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-export.cmake"
    )
    export(PACKAGE ${PROJECT_NAME})

    # Uninstallation
    if(NOT TARGET uninstall AND PROJECT_IS_TOP_LEVEL)
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
