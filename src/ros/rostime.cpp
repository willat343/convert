#include "convert/ros/rostime.hpp"

namespace convert {

template void to<std::chrono::time_point<std::chrono::steady_clock>>(const ros::Time&,
        std::chrono::time_point<std::chrono::steady_clock>&);
template void to<std::chrono::time_point<std::chrono::system_clock>>(const ros::Time&,
        std::chrono::time_point<std::chrono::system_clock>&);
template void to<std::chrono::time_point<std::chrono::steady_clock>>(
        const std::chrono::time_point<std::chrono::steady_clock>&, ros::Time&);
template void to<std::chrono::time_point<std::chrono::system_clock>>(
        const std::chrono::time_point<std::chrono::system_clock>&, ros::Time&);

}
