#include "convert/ros/std_msgs.hpp"

namespace convert {

template void to<std::chrono::time_point<std::chrono::steady_clock>>(const std_msgs::Header&,
        std::chrono::time_point<std::chrono::steady_clock>& tp, std::string& frame_id);
template void to<std::chrono::time_point<std::chrono::system_clock>>(const std_msgs::Header&,
        std::chrono::time_point<std::chrono::system_clock>& tp, std::string& frame_id);
template void to<std::chrono::time_point<std::chrono::steady_clock>>(
        const std::chrono::time_point<std::chrono::steady_clock>& tp, const std::string& frame_id, std_msgs::Header&);
template void to<std::chrono::time_point<std::chrono::system_clock>>(
        const std::chrono::time_point<std::chrono::system_clock>& tp, const std::string& frame_id, std_msgs::Header&);

}
