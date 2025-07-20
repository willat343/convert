# convert

Generic type conversion library supporting a variety of data structures.

## Core C++ Library

### Prerequisites

| **Dependency** | **Version** | **Description** |
|----------------|-------------|-----------------|
| CMake | >= 3.21 | CMake Build Tool |
| [cmakebox](https://github.com/willat343/cmakebox) | >= 0.0.1 | CMake Functions and Utilities |
| [Eigen3] | >= 3.4.0 | Linear Algebra Package |
| [GTSAM] | - | GATech Smooth and Mapping Package |
| [manif] | >= 0.0.6 | Lie Theory Package |
| [MATLAB] | - | MATLAB CXX Interfaces |
| [ROS] | noetic | Various standard ROS packages |
| [[sensorbox](https://github.com/willat343/sensorbox)] | 0.6.0 | Sensor Processing Package |

Note that square brackets indicate optional dependencies.

There are several ways to include `convert` within your project:
- [Preferred] Via `FetchContent` allowing package to be built as a submodule.
- Via `find_package`, requiring package to be installed to the system, locally, or to a catkin workspace.

## Include via FetchContent

It is recommended to leverage the functionality of [cmakebox](https://github.com/willat343/cmakebox) by including the following lines in the `CMakeLists.txt` (replace `X.Y.Z` with version):
```CMake
set(CMAKEBOX_VERSION "0.0.1")
FetchContent_Declare(
    cmakebox
    GIT_REPOSITORY git@github.com:willat343/cmakebox.git
    GIT_TAG v${CMAKEBOX_VERSION}
)
FetchContent_MakeAvailable(cmakebox)
list(APPEND CMAKE_MODULE_PATH "${cmakebox_SOURCE_DIR}/cmake")
include(CMakeBox)

set(CONVERT_VERSION "X.Y.Z")
import_dependency(
    convert
    TARGET convert::convert
    VERSION ${CONVERT_VERSION}
    USE_SYSTEM_REQUIRED_VERSION ${CONVERT_VERSION}
    GIT_REPOSITORY git@github.com:willat343/convert
    GIT_TAG v${CONVERT_VERSION}
)
```

Without relying on [cmakebox](https://github.com/willat343/cmakebox), this can be achieved with (replace `X.Y.Z` with version):
```CMake
set(CONVERT_VERSION "X.Y.Z")
FetchContent_Declare(
    convert
    GIT_REPOSITORY git@github.com:willat343/convert
    GIT_TAG        v${CONVERT_VERSION}
)
FetchContent_MakeAvailable(convert)
```

## Include via Install

### Clone

```bash
git clone git@github.com:willat343/cppbox.git
cd cppbox
```

### Configure

For system install:
```bash
cmake -S . -B build
```

For local install:
```bash
cmake -S . -B build -DCMAKE_INSTALL_DIR=$HOME/.local
```

### Build

```bash
cmake --build build -j
```

### Install

```bash
sudo cmake --build build --target install
```

### Include

Include with the following lines in the `CMakeLists.txt`:
```CMake
find_package(convert REQUIRED)
target_link_libraries(<target> PUBLIC convert::convert)
target_include_directories(<target> SYSTEM <PUBLIC|INTERFACE|PRIVATE> ${convert_INCLUDE_DIRS})
```
Note that it is important to call `target_link_libraries` **before** `target_include_directories` because the `${convert_LIBRARIES}` targets may contain compilation definitions that are required within the public header files in `${convert_INCLUDE_DIRS}`. In particular, these compile definitions are needed to enable the headers for enabled components in `<convert/convert.hpp>`.

### Uninstall

```bash
sudo cmake --build build --target uninstall
```

For more explicit output, the test executables can be run directly from the build directory.

## Include in Catkin Workspace

A `package.xml` is supplied to facilitate an isolated installation within a catkin workspace (e.g. for ROS applications).

### Clone

```bash
cd /path/to/catkin_ws/src
git clone git@github.com:willat343/convert.git
```

### Build

```bash
cd /path/to/catkin_ws
catkin build convert
```

### Include

To use the package in a downstream project, one should add to their `package.xml`:
```xml
<depend>convert</depend>
```

One can then include `convert` package by includeing in the `CMakeLists.txt`:
```CMake
find_package(convert REQUIRED)
target_link_libraries(<target> PUBLIC convert::convert)
```

### Clean

```bash
cd /path/to/catkin_ws
catkin clean convert
```

## Usage

Include all built functions and helpers with:
```cpp
#include <convert/convert.hpp>
```

Alternatively, include only the required conversion, and the helpers (must be after), e.g.
```cpp
#include <convert/eigen_ros/eigen_ros.hpp>
#include <convert/convert_helpers.hpp>
```

For one-to-one conversions, the function definitions are of form:
```cpp
void to(const FromType& in, ToType& out);
```

This function can be used directly (e.g. if `ToType` already exists) or using the helpers, one can simply write:
```cpp
ToType out = to<ToType>(in);
```

There is also a helper for 2-to-1 mappings, however currently all template types sometimes need to be provided to avoid overload confusion:
```cpp
ToType out = to<ToType, From1Type, From2Type>(from1, from2);
```

For multi-to-one, one-to-multi, multi-to-multi and other special conversions, consult the documentation.

Note that some conversions are lossy or incomplete, if the input contains more or less data than the output. When this occurs, it is (or should be) documented. The user is responsible for using conversions suitable for their purpose.

## Documentation

Documentation must be turned on by setting the `-DBUILD_DOCUMENTATION=ON` cmake argument.

To view the HTML documentation, open the `build/docs/html/index.html` file.

To view the LaTeX documentation, build it with:
```bash
cd build/docs/latex
make
```
Then open the file `refman.pdf`.

## Tests

Tests must be turned on by setting the `-DBUILD_TESTS=ON` cmake argument.

They can then be run with `ctest`:
```bash
ctest --test-dir test
```
