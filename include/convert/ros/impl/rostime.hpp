#ifndef CONVERT_ROS_IMPL_ROSTIME_HPP
#define CONVERT_ROS_IMPL_ROSTIME_HPP

#include "convert/ros/rostime.hpp"

namespace convert {

template<typename Clock, typename Duration>
void to(const ros::Time& t, std::chrono::time_point<Clock, Duration>& tp) {
    tp = std::chrono::time_point<Clock, Duration>(std::chrono::seconds(t.sec) + std::chrono::nanoseconds(t.nsec));
}

template<typename Clock, typename Duration>
void to(const std::chrono::time_point<Clock, Duration>& tp, ros::Time& t) {
    // duration_cast always rounds down
    t.sec = std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch()).count();
    t.nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(
            tp - std::chrono::time_point<Clock, Duration>(std::chrono::seconds(t.sec)))
                     .count();
}

}

#endif
