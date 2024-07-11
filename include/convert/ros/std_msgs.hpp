#ifndef CONVERT_ROS_STD_MSGS_HPP
#define CONVERT_ROS_STD_MSGS_HPP

#include <std_msgs/Header.h>
#include <ros/time.h>

#include <chrono>
#include <string>

namespace convert {

/**
 * @brief Convert header to time_point and frame id string. The sequence ID is ignored/lost.
 * 
 * @tparam Clock 
 * @tparam Clock::Duration 
 * @param header 
 * @param tp 
 * @param frame_id 
 */
template<typename Clock, typename Duration = typename Clock::Duration>
void to(const std_msgs::Header& header, std::chrono::time_point<Clock, Duration>& tp, std::string& frame_id);

/**
 * @brief Convert time_point and frame id string to header. The sequence ID is set to 0.
 * 
 * @tparam Clock 
 * @tparam Clock::Duration 
 * @param tp 
 * @param frame_id 
 * @param header 
 */
template<typename Clock, typename Duration = typename Clock::Duration>
void to(const std::chrono::time_point<Clock, Duration>& tp, const std::string& frame_id, std_msgs::Header& header);

}

#include "convert/ros/impl/std_msgs.hpp"

#endif
