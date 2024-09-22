# convert_catkin

Catkin wrapper for convert, which allows the library to be built and installed to a catkin workspace.

## Build

```bash
cd /path/to/catkin_ws/src
ln -s /path/to/convert
cd /path/to/catkin_ws
catkin build convert_catkin
```

Downstream packages built within the catkin workspace can depend on `convert_catkin` and can find the core library with `find_package(convert REQUIRED)`.
