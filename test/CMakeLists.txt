set(CONVERT_TEST_SRC_FILES "")
set(CONVERT_TEST_DEFINITIONS ${CONVERT_DEFINITIONS})
set(CONVERT_TEST_SYSTEM_INCLUDE_DIRS ${CONVERT_SYSTEM_INCLUDE_DIRS})
set(CONVERT_TEST_SYSTEM_LIBRARIES
    ${CONVERT_SYSTEM_LIBRARIES}
    gtest_main
    gtest
    pthread
)

if (BUILD_EIGEN_COMPONENTS AND BUILD_ROS_COMPONENTS)
    # Append to source files
    list(APPEND CONVERT_TEST_SRC_FILES
        src/eigen_ros/geometry_msgs.cpp
    )
endif()

if (BUILD_MANIF_COMPONENTS AND BUILD_ROS_COMPONENTS)
    # Append to source files
    list(APPEND CONVERT_TEST_SRC_FILES
        src/manif_ros/geometry_msgs.cpp
    )
endif()

if (BUILD_ROS_COMPONENTS)
    # Append to source files
    list(APPEND CONVERT_TEST_SRC_FILES
        src/ros/rostime.cpp
        src/ros/std_msgs.cpp
    )
endif()

if (BUILD_SENSORBOX_COMPONENTS AND BUILD_ROS_COMPONENTS)
    # Append to source files
    list(APPEND CONVERT_TEST_SRC_FILES
        src/sensorbox_ros/imu.cpp
    )
endif()

if (CONVERT_TEST_SRC_FILES)
    message(DEBUG "Building convert library tests as ${PROJECT_NAME}_tests with\n\
        CONVERT_TEST_SRC_FILES = ${CONVERT_TEST_SRC_FILES}\n\
        CONVERT_TEST_DEFINITIONS = ${CONVERT_TEST_DEFINITIONS}\n\
        CONVERT_TEST_SYSTEM_INCLUDE_DIRS = ${CONVERT_TEST_SYSTEM_INCLUDE_DIRS}\n\
        CONVERT_TEST_SYSTEM_LIBRARIES = ${CONVERT_TEST_SYSTEM_LIBRARIES}")

    # Build tests
    add_executable(${PROJECT_NAME}_tests
        ${CONVERT_TEST_SRC_FILES}
    )

    # Definitions
    target_compile_definitions(${PROJECT_NAME}_tests PUBLIC ${CONVERT_TEST_DEFINITIONS})

    # Properties
    set_target_properties(${PROJECT_NAME}_tests PROPERTIES
        CXX_STANDARD 20
    )

    # Compile Options
    target_compile_options(${PROJECT_NAME}_tests PRIVATE
        -Wall -Wextra -Wpedantic -ftemplate-backtrace-limit=${TEMPLATE_BACKTRACE_LIMIT}
    )

    # Include Directories
    target_include_directories(${PROJECT_NAME}_tests PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    )

    # System Include Directories
    target_include_directories(${PROJECT_NAME}_tests SYSTEM PUBLIC
        ${CONVERT_TEST_SYSTEM_INCLUDE_DIRS}
    )

    # Link Libraries
    target_link_libraries(${PROJECT_NAME}_tests PUBLIC
        convert
        ${CONVERT_TEST_SYSTEM_LIBRARIES}
    )

    # Enable ctest
    enable_testing()
    add_test(NAME ${PROJECT_NAME}_tests COMMAND ${PROJECT_NAME}_tests)
else()
    message(WARNING "Not building convert library tests, possibly because no tests yet exist for the specified \
        combination of components.")
endif()
