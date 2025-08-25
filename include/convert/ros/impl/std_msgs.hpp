#ifndef CONVERT_ROS_IMPL_STD_MSGS_HPP
#define CONVERT_ROS_IMPL_STD_MSGS_HPP

#include "convert/ros/ros.hpp"
#include "convert/ros/std_msgs.hpp"

namespace convert {

template<cppbox::IsTimePoint TimePoint>
void to(const std_msgs::Header& header, TimePoint& tp, std::string& frame_id) {
    to(header.stamp, tp);
    frame_id = header.frame_id;
}

template<cppbox::IsTimePoint TimePoint>
void to(const TimePoint& tp, const std::string& frame_id, std_msgs::Header& header) {
    header.seq = 0;
    to(tp, header.stamp);
    header.frame_id = frame_id;
}

}

#if !CONVERT_HEADER_ONLY
namespace convert {

extern template void to<std::chrono::time_point<std::chrono::steady_clock>>(const std_msgs::Header&,
        std::chrono::time_point<std::chrono::steady_clock>& tp, std::string& frame_id);
extern template void to<std::chrono::time_point<std::chrono::system_clock>>(const std_msgs::Header&,
        std::chrono::time_point<std::chrono::system_clock>& tp, std::string& frame_id);
extern template void to<std::chrono::time_point<std::chrono::steady_clock>>(
        const std::chrono::time_point<std::chrono::steady_clock>& tp, const std::string& frame_id, std_msgs::Header&);
extern template void to<std::chrono::time_point<std::chrono::system_clock>>(
        const std::chrono::time_point<std::chrono::system_clock>& tp, const std::string& frame_id, std_msgs::Header&);

}
#endif

#endif
