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

if (CONVERT_TEST_SRC_FILES)
    set(CONVERT_LIBRARY_TESTS ${CONVERT_LIBRARY}_tests)
    message(DEBUG "Building convert library tests as ${CONVERT_LIBRARY_TESTS} with\n\
        CONVERT_TEST_SRC_FILES = ${CONVERT_TEST_SRC_FILES}\n\
        CONVERT_TEST_DEFINITIONS = ${CONVERT_TEST_DEFINITIONS}\n\
        CONVERT_TEST_SYSTEM_INCLUDE_DIRS = ${CONVERT_TEST_SYSTEM_INCLUDE_DIRS}\n\
        CONVERT_TEST_SYSTEM_LIBRARIES = ${CONVERT_TEST_SYSTEM_LIBRARIES}")

    # Build Library
    add_executable(${CONVERT_LIBRARY_TESTS}
        ${CONVERT_TEST_SRC_FILES}
    )

    # Definitions
    target_compile_definitions(${CONVERT_LIBRARY_TESTS} PUBLIC ${CONVERT_TEST_DEFINITIONS})

    # Properties
    set_target_properties(${CONVERT_LIBRARY_TESTS} PROPERTIES
        CXX_STANDARD 20
    )

    # Compile Options
    target_compile_options(${CONVERT_LIBRARY_TESTS} PRIVATE
        -Wall -Wextra -Wpedantic -ftemplate-backtrace-limit=${TEMPLATE_BACKTRACE_LIMIT}
    )

    # Include Directories
    target_include_directories(${CONVERT_LIBRARY_TESTS} PUBLIC
        include
        ../include
    )

    # System Include Directories
    target_include_directories(${CONVERT_LIBRARY_TESTS} SYSTEM PUBLIC
        ${CONVERT_TEST_SYSTEM_INCLUDE_DIRS}
    )

    # Link Libraries
    target_link_libraries(${CONVERT_LIBRARY_TESTS} PUBLIC
        convert
        ${CONVERT_TEST_SYSTEM_LIBRARIES}
    )

    # Enable ctest
    enable_testing()
    add_test(NAME ${CONVERT_LIBRARY_TESTS} COMMAND ${CONVERT_LIBRARY_TESTS})
else()
    message(WARNING "Not building convert library tests, possibly because no tests yet exist for the specified \
        combination of components.")
endif()
