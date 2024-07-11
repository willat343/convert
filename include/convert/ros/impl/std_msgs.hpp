#ifndef CONVERT_ROS_IMPL_STD_MSGS_HPP
#define CONVERT_ROS_IMPL_STD_MSGS_HPP

#include "convert/ros/ros.hpp"
#include "convert/ros/std_msgs.hpp"

namespace convert {

template<typename Clock, typename Duration>
void to(const std_msgs::Header& header, std::chrono::time_point<Clock, Duration>& tp, std::string& frame_id) {
    to(header.stamp, tp);
    frame_id = header.frame_id;
}

template<typename Clock, typename Duration>
void to(const std::chrono::time_point<Clock, Duration>& tp, const std::string& frame_id, std_msgs::Header& header) {
    to(tp, header.stamp);
    header.frame_id = frame_id;
}

}

#endif
