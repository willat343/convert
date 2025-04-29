set(convert_TEST_SRC_FILES "")
set(convert_TEST_DEFINITIONS ${convert_DEFINITIONS})
set(convert_TEST_SYSTEM_INCLUDE_DIRS ${convert_SYSTEM_INCLUDE_DIRS})
set(convert_TEST_SYSTEM_LIBRARIES
    ${convert_SYSTEM_LIBRARIES}
    gtest_main
    gtest
    pthread
)

if (BUILD_EIGEN_COMPONENTS AND BUILD_ROS_COMPONENTS)
    # Append to source files
    list(APPEND convert_TEST_SRC_FILES
        src/eigen_ros/geometry_msgs.cpp
    )
endif()

if (BUILD_MANIF_COMPONENTS AND BUILD_ROS_COMPONENTS)
    # Append to source files
    list(APPEND convert_TEST_SRC_FILES
        src/manif_ros/geometry_msgs.cpp
    )
endif()

if (BUILD_ROS_COMPONENTS)
    # Append to source files
    list(APPEND convert_TEST_SRC_FILES
        src/ros/rostime.cpp
        src/ros/std_msgs.cpp
    )
endif()

if (BUILD_SENSORBOX_COMPONENTS AND BUILD_ROS_COMPONENTS)
    # Append to source files
    list(APPEND convert_TEST_SRC_FILES
        src/sensorbox_ros/imu.cpp
    )
endif()

if (convert_TEST_SRC_FILES)
    message(DEBUG "Building convert library tests as ${PROJECT_NAME}_tests with\n\
        convert_TEST_SRC_FILES = ${convert_TEST_SRC_FILES}\n\
        convert_TEST_DEFINITIONS = ${convert_TEST_DEFINITIONS}\n\
        convert_TEST_SYSTEM_INCLUDE_DIRS = ${convert_TEST_SYSTEM_INCLUDE_DIRS}\n\
        convert_TEST_SYSTEM_LIBRARIES = ${convert_TEST_SYSTEM_LIBRARIES}")

    # Build tests
    add_executable(${PROJECT_NAME}_tests
        ${convert_TEST_SRC_FILES}
    )

    # Definitions
    target_compile_definitions(${PROJECT_NAME}_tests PUBLIC ${convert_TEST_DEFINITIONS})

    # Properties
    set_target_properties(${PROJECT_NAME}_tests PROPERTIES
        CXX_STANDARD 20
    )

    # Ensure the tests link to the built library, not installed library (this works by setting BUILD_RPATH, and then
    # stopping the linker from setting RUNPATH instead of RPATH (RPATH is checked before LD_LIBRARY_PATH, while
    # RUNPATH is checked after))
    target_link_options(${PROJECT_NAME}_tests PUBLIC
        -Wl,--disable-new-dtags
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
        ${convert_TEST_SYSTEM_INCLUDE_DIRS}
    )

    # Link Libraries
    target_link_libraries(${PROJECT_NAME}_tests PUBLIC
        ${PROJECT_NAME}
        ${convert_TEST_SYSTEM_LIBRARIES}
    )

    # Enable ctest
    enable_testing()
    add_test(NAME ${PROJECT_NAME}_tests COMMAND ${PROJECT_NAME}_tests)
else()
    message(WARNING "Not building convert library tests, possibly because no tests yet exist for the specified \
        combination of components.")
endif()
