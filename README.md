# convert

## Build

It is recommended that you configure with `ccmake` (`sudo apt install cmake-curses-gui`) to see the various options. Otherwise use `cmake` instead of `ccmake` and set flags manually.
```bash
mkdir build && cd build
ccmake ..
make -j
```

## Install/Uninstall

Install with:
```bash
sudo make install
```

Uninstall with:
```bash
sudo make uninstall
```

## Usage

`cmake` can be employed to use this library in your work. Having installed `convert` to your system, add the following lines to your project's `CMakeLists.txt`:
```cmake
find_package(convert REQUIRED)
```

Include the directories with your target:
```cmake
target_include_directories(your_target SYSTEM PUBLIC ${convert_INCLUDE_DIRS})
```

Link to the library:
```cmake
target_link_libraries(your_target PUBLIC ${convert_LIBRARIES})
```

Add definitions to target (to enable module headers in `<convert/convert.hpp>`):
```cmake
target_compile_definitions(your_target PUBLIC ${convert_DEFINITIONS})
```

Then in your code, include all built functions and helpers with:
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

Documentation must be turned on (manually or via `ccmake`):

```bash
cd build
cmake -DBUILD_DOCUMENTATION=ON ..
make -j
```

To view the HTML documentation, open the `build/docs/html/index.html` file.

To view the LaTeX documentation, build it with:
```bash
cd build/docs/latex
make
```
Then open the file `refman.pdf`.

## Changelog

* [04.07.2024] Migrated from `continuity`
