#ifndef CONVERT_ROS_IMPL_ROSTIME_HPP
#define CONVERT_ROS_IMPL_ROSTIME_HPP

#include "convert/ros/rostime.hpp"

namespace convert {

template<cppbox::IsTimePoint TimePoint>
void to(const ros::Time& t, TimePoint& tp) {
    tp = TimePoint(std::chrono::seconds(t.sec) + std::chrono::nanoseconds(t.nsec));
}

template<cppbox::IsTimePoint TimePoint>
void to(const TimePoint& tp, ros::Time& t) {
    // duration_cast always rounds down
    t.sec = std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch()).count();
    t.nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(tp - TimePoint(std::chrono::seconds(t.sec))).count();
}

}

#if !CONVERT_HEADER_ONLY
namespace convert {

extern template void to<std::chrono::time_point<std::chrono::steady_clock>>(const ros::Time&,
        std::chrono::time_point<std::chrono::steady_clock>&);
extern template void to<std::chrono::time_point<std::chrono::system_clock>>(const ros::Time&,
        std::chrono::time_point<std::chrono::system_clock>&);
extern template void to<std::chrono::time_point<std::chrono::steady_clock>>(
        const std::chrono::time_point<std::chrono::steady_clock>&, ros::Time&);
extern template void to<std::chrono::time_point<std::chrono::system_clock>>(
        const std::chrono::time_point<std::chrono::system_clock>&, ros::Time&);

}
#endif

#endif
