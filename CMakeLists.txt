cmake_minimum_required(VERSION 3.21)
project(convert
    VERSION 0.6.2
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
option(BUILD_DOCUMENTATION "Build Doxygen Documentation" OFF)
option(BUILD_EIGEN_COMPONENTS "Build Eigen Components" OFF)
option(BUILD_MANIF_COMPONENTS "Build manif Components" OFF)
option(BUILD_FOXGLOVE_COMPONENTS "Build foxglove Components" OFF)
option(BUILD_GTSAM_COMPONENTS "Build GTSAM Components" OFF)
option(BUILD_MATLAB_COMPONENTS "Build MATLAB Components" OFF)
option(BUILD_ROS_COMPONENTS "Build ROS Components" OFF)
option(BUILD_SHARED_LIBS "Build shared library (if CONVERT_HEADER_ONLY=OFF)" OFF)
option(CONVERT_HEADER_ONLY "Build library as header-only" OFF)
option(DEVELOPER_MODE "Use local versions of cmakebox, cppbox, mathbox, and convert" OFF)

# Configure FetchContent source directories for DEVELOPER_MODE
if (DEVELOPER_MODE)
    set(FETCHCONTENT_SOURCE_DIR_CMAKEBOX "${CMAKE_SOURCE_DIR}/dependencies/cmakebox")
    set(FETCHCONTENT_SOURCE_DIR_CPPBOX "${CMAKE_SOURCE_DIR}/dependencies/cppbox")
endif()

# Enforce component dependencies (internal to convert, not external library dependencies)
if (BUILD_MANIF_COMPONENTS AND NOT BUILD_EIGEN_COMPONENTS)
    message(ERROR "BUILD_MANIF_COMPONENTS was enabled but it relies on BUILD_EIGEN_COMPONENTS which \
            was not enabled (either disabled or Eigen3 was not found).")
endif()

# Dependency: cmakebox
set(CMAKEBOX_VERSION "0.0.8")
FetchContent_Declare(
    cmakebox
    GIT_REPOSITORY git@github.com:willat343/cmakebox.git
    GIT_TAG v${CMAKEBOX_VERSION}
)
FetchContent_MakeAvailable(cmakebox)
list(APPEND CMAKE_MODULE_PATH "${cmakebox_SOURCE_DIR}/cmake")
include(CMakeBox)

# CMake Build Type
setup_build_type()

# Get CXX Compiler Information
get_cxx_compiler_info()

# Dependency: cppbox (Target: cppbox::cppbox)
set(CPPBOX_VERSION "0.1.4")
import_dependency(
    cppbox
    TARGET cppbox::cppbox
    METHOD FETCH_GIT
    FIND_PACKAGE_VERSION ${CPPBOX_VERSION}
    GIT_REPOSITORY git@github.com:willat343/cppbox.git
    GIT_TAG v${CPPBOX_VERSION}
)

# Optional Dependency: Eigen3 (Target: Eigen3::Eigen)
if (BUILD_EIGEN_COMPONENTS)
    set(EIGEN3_VERSION "3.4.0")
    import_Eigen3(
        VERSION ${EIGEN3_VERSION}
    )
endif()

# Optional Dependency: foxglove (Target: foxglove::foxglove)
if (BUILD_FOXGLOVE_COMPONENTS)
    set(FOXGLOVE_VERSION "0.10.1")
    import_foxglove(
        VERSION ${FOXGLOVE_VERSION}
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

# Get number of components to build
SET(NUM_BUILD_COMPONENTS 0)
foreach(BUILD_COMPONENT
    BUILD_EIGEN_COMPONENTS
    BUILD_MANIF_COMPONENTS
    BUILD_FOXGLOVE_COMPONENTS
    BUILD_GTSAM_COMPONENTS
    BUILD_MATLAB_COMPONENTS
    BUILD_ROS_COMPONENTS)
    if (${BUILD_COMPONENT})
        math(EXPR NUM_BUILD_COMPONENTS "${NUM_BUILD_COMPONENTS} + 1")
    endif()
endforeach()

# Variables
set(convert_SRC_FILES "")
set(convert_DEFINITIONS "")
set(convert_SYSTEM_INCLUDE_DIRS "")
set(convert_SYSTEM_LIBRARIES "cppbox::cppbox")
set(convert_EXPORT_TARGETS "")

# Process components in dependency order so that convert_SYSTEM_LIBRARIES order has most dependent libraries first.
# Header-only libraries can be flexible in their ordering.
# The external library dependencies are:
#   manif -> Eigen (header-only)
#   gtsam -> Eigen (header-only)

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

if (BUILD_FOXGLOVE_COMPONENTS)
    # Append to source files
    list(APPEND convert_SRC_FILES
        src/foxglove_std/foxglove_std.cpp
    )

    # Append to definitions
    list(APPEND convert_DEFINITIONS CONVERT_FOXGLOVE)

    # Append to system libraries
    list(APPEND convert_SYSTEM_LIBRARIES
        foxglove::foxglove
    )

    # Append to export targets
    list(APPEND convert_EXPORT_TARGETS
        ${foxglove_REAL_TARGET}
    )

    if (BUILD_EIGEN_COMPONENTS)
        # Append to source files
        list(APPEND convert_SRC_FILES
            src/eigen_foxglove/eigen_foxglove.cpp
        )

        # Append to definitions
        list(APPEND convert_DEFINITIONS CONVERT_EIGEN)

        # Append to system libraries
        list(APPEND convert_SYSTEM_LIBRARIES
            Eigen3::Eigen
        )
    endif()
endif()

if (BUILD_ROS_COMPONENTS)
    # Append to source files
    list(APPEND convert_SRC_FILES
        src/ros/geometry_msgs_nav_msgs.cpp
        src/ros/nav_msgs.cpp
        src/ros/rostime.cpp
        src/ros/std_msgs.cpp
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
    # Append to source files
    list(APPEND convert_SRC_FILES
        src/matlab_std/matlab_std.cpp
    )

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
    # Append to source files
    list(APPEND convert_SRC_FILES
        src/eigen/geometry.cpp
        src/eigen_std/eigen_std.cpp
    )

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
list(REMOVE_DUPLICATES convert_EXPORT_TARGETS)

# Report components that will be built
message(NOTICE "Components (${NUM_BUILD_COMPONENTS} ENABLED):")
message(NOTICE "\t    EIGEN = ${BUILD_EIGEN_COMPONENTS}")
message(NOTICE "\t FOXGLOVE = ${BUILD_FOXGLOVE_COMPONENTS}")
message(NOTICE "\t    GTSAM = ${BUILD_GTSAM_COMPONENTS}")
message(NOTICE "\t    MANIF = ${BUILD_MANIF_COMPONENTS}")
message(NOTICE "\t   MATLAB = ${BUILD_MATLAB_COMPONENTS}")
message(NOTICE "\t      ROS = ${BUILD_ROS_COMPONENTS}")

# Compile of library and tests
if (NUM_BUILD_COMPONENTS GREATER 0)
    # Build Library
    set(LIBRARY_NAME ${PROJECT_NAME})
    if (CONVERT_HEADER_ONLY OR NOT convert_SRC_FILES)
        # Build interface library
        add_library(${LIBRARY_NAME} INTERFACE)
        set(PUBLIC_OR_INTERFACE INTERFACE)
    else()
        # Shared/Static Library (determined by BUILD_SHARED_LIBS)
        add_library(${LIBRARY_NAME}
            ${convert_SRC_FILES}
        )
        set(PUBLIC_OR_INTERFACE PUBLIC)

        # Private Compile Options
        target_compile_options(${LIBRARY_NAME} PRIVATE
            -Wall -Wextra -Wpedantic
        )
    endif()
    add_library(${PROJECT_NAME}::${LIBRARY_NAME} ALIAS ${LIBRARY_NAME})
    message(DEBUG "Building ${PROJECT_NAME}::${LIBRARY_NAME} library with\n\
        CONVERT_HEADER_ONLY = ${CONVERT_HEADER_ONLY}\n\
        convert_SRC_FILES = ${convert_SRC_FILES}\n\
        convert_DEFINITIONS = ${convert_DEFINITIONS}\n\
        convert_SYSTEM_INCLUDE_DIRS = ${convert_SYSTEM_INCLUDE_DIRS}\n\
        convert_SYSTEM_LIBRARIES = ${convert_SYSTEM_LIBRARIES}")

    # Compile Definitions
    target_compile_definitions(${LIBRARY_NAME} ${PUBLIC_OR_INTERFACE}
        CONVERT_HEADER_ONLY=$<IF:$<BOOL:${CONVERT_HEADER_ONLY}>,1,0>
        ${convert_DEFINITIONS}
    )

    # Properties
    set_target_properties(${LIBRARY_NAME} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        POSITION_INDEPENDENT_CODE ON
    )

    # Include directories
    target_include_directories(${LIBRARY_NAME} ${PUBLIC_OR_INTERFACE}
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )

    # System include directories
    target_include_directories(${LIBRARY_NAME} SYSTEM ${PUBLIC_OR_INTERFACE}
        ${convert_SYSTEM_INCLUDE_DIRS}
    )

    # Link libraries
    target_link_libraries(${LIBRARY_NAME} ${PUBLIC_OR_INTERFACE}
        ${convert_SYSTEM_LIBRARIES}
    )

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
        TARGETS ${LIBRARY_NAME} ${convert_EXPORT_TARGETS}
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
    create_uninstall_target()

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

    # Build tests
    if(BUILD_TESTS)
        add_subdirectory(test)
    endif()
else()
    message(WARNING "Not building convert package, possibly because no valid combination of components was enabled.")
endif()
