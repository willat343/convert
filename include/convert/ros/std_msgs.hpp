#ifndef CONVERT_ROS_STD_MSGS_HPP
#define CONVERT_ROS_STD_MSGS_HPP

#include <ros/time.h>
#include <std_msgs/Header.h>

#include <chrono>
#include <cppbox/time.hpp>
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
template<cppbox::IsTimePoint TimePoint>
void to(const std_msgs::Header& header, TimePoint& tp, std::string& frame_id);

/**
 * @brief Convert time_point and frame id string to header. The sequence ID is set to 0.
 *
 * @tparam Clock
 * @tparam Clock::Duration
 * @param tp
 * @param frame_id
 * @param header
 */
template<cppbox::IsTimePoint TimePoint>
void to(const TimePoint& tp, const std::string& frame_id, std_msgs::Header& header);

}

#include "convert/ros/impl/std_msgs.hpp"

#endif
