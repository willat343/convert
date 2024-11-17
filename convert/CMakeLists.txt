cmake_minimum_required(VERSION 3.12) # 3.12 required for: add_compile_definitions
project(convert
    VERSION 0.2.0
    DESCRIPTION "Conversion Library"
    LANGUAGES CXX
)

# Setup
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/setup.cmake)

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

    # Link libraries
    target_link_libraries(${PROJECT_NAME} PUBLIC
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
