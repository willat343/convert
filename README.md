# convert

## Build

It is recommended that you configure with `ccmake` (`sudo apt install cmake-curses-gui`) to see the various options. To do so, replace `cmake` with `ccmake` in the below instructions.

```bash
mkdir build && cd build
cmake ..
make -j
```

## Usage

Include all built functions and helpers with:
```cpp
#include <convert/convert.hpp>
```

Alternatively, it is recommended to include the helpers after the header of the required conversion, e.g.
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

For multi-to-one, one-to-multi or multi-to-multi conversions, consult the documentation.

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
