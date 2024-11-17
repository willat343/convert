# convert

Generic type conversion library supporting a variety of data structures.

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
