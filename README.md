# convert

Generic type conversion library supporting a variety of data structures.

## Core C++ Library

### Prerequisites

| **Dependency** | **Version** | **Description** |
|----------------|-------------|-----------------|
| [Eigen3] | >= 3.3 | Linear Algebra Package |
| [GTSAM] | - | GATech Smooth and Mapping Package |
| [manif] | - | Lie Theory Package |
| [MATLAB] | - | MATLAB CXX Interfaces |
| [ROS] | noetic | Various standard ROS packages |
| [[sensorbox](https://github.com/willat343/sensorbox)] | 0.3 | Sensor Processing Package |

Note that square brackets indicate optional dependencies.

### Installation

It is recommended that you configure with `ccmake` (`sudo apt install cmake-curses-gui`) to see the various options. Otherwise use `cmake` instead of `ccmake` and set flags manually.

```bash
cd convert
mkdir build && cd build
ccmake ..
make -j
sudo make install
```

Note that the library will attempt to build as many of the components as possible.

### Uninstallation

```bash
cd build
sudo make uninstall
```

### Usage

Import the package into your project and add the dependency to your target `<target>` with:
```cmake
find_package(convert REQUIRED)
target_link_libraries(<target> <PUBLIC|INTERFACE|PRIVATE> ${convert_LIBRARIES})
target_include_directories(<target> SYSTEM <PUBLIC|INTERFACE|PRIVATE> ${convert_INCLUDE_DIRS})
```
Note that it is important to call `target_link_libraries` **before** `target_include_directories` because the `${convert_LIBRARIES}` targets may contain compilation definitions that are required within the public header files in `${convert_INCLUDE_DIRS}`. In particular, these compile definitions are needed to enable the headers for enabled components in `<convert/convert.hpp>`.

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

### Documentation

Documentation must be turned on by setting the `-DBUILD_DOCUMENTATION=ON` cmake argument.

To view the HTML documentation, open the `build/docs/html/index.html` file.

To view the LaTeX documentation, build it with:
```bash
cd build/docs/latex
make
```
Then open the file `refman.pdf`.

### Tests

Tests must be turned on by setting the `-DBUILD_TESTS=ON` cmake argument.

```bash
cd build
cmake -DBUILD_TESTS=ON ..
make -j
```

They can then be run with `ctest`:
```bash
ctest --test-dir test
```

For more explicit output, the test executables can be run directly from the build directory.

## Catkin Support

A `package.xml` is supplied to facilitate an isolated installation within a catkin workspace (e.g. for ROS applications).

### Prerequisites

Prerequisites of core C++ library plus the following:

| **Dependency** | **Version** | **Description** |
|----------------|-------------|-----------------|
| catkin | - | catkin build system |

### Installation

To use this package with catkin, simply clone or symlink the repository to the workspace's `src` directory, for example:
```bash
ln -s /path/to/convert /path/to/catkin_ws/src
```

```bash
cd /path/to/catkin_ws
catkin build convert
```

### Uninstallation

```bash
cd /path/to/catkin_ws
catkin clean convert
```

### Usage

To use the package in a downstream project, one should add to their `package.xml`:
```xml
<depend>convert</depend>
```
One can then either use the workspace's isolated installation or use the system installation otherwise.
Importing the dependency is then exactly the same as it would be in a non-catkin package as described above (do NOT rely on the `catkin` variables like `catkin_LIBRARIES` and `catkin_INCLUDE_DIRS`).

### Documentation

Documentation must be turned on by setting the `-DBUILD_DOCUMENTATION=ON` cmake argument. This can be done in catkin with:
```bash
catkin config --cmake-args -DBUILD_DOCUMENTATION=ON
```

### Tests

Tests must be turned on by setting the `-DBUILD_TESTS=ON` cmake argument. This can be done in catkin with:
```bash
catkin config --cmake-args -DBUILD_TESTS=ON
```
