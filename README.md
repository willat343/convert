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

For more information, see [convert/README.md](convert/README.md) and documentation.

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

A catkin wrapper is available to facilitate an isolated installation within a catkin workspace (e.g. for ROS applications).

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
catkin build convert_catkin
```

### Uninstallation

```bash
cd /path/to/catkin_ws
catkin clean convert_catkin
```

### Usage

To use the package in a downstream project, one should add to their `package.xml`:
```xml
<exec_depend>convert_catkin</exec_depend>
```
One can then either use the workspace's isolated installation if the catkin wrapper exists in the workspace, or use the system installation otherwise.
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
