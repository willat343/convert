#ifndef CONVERT_ROS_ROSTIME_HPP
#define CONVERT_ROS_ROSTIME_HPP

#include <ros/time.h>

#include <chrono>

namespace convert {

template<typename Clock, typename Duration = typename Clock::duration>
void to(const ros::Time& t, std::chrono::time_point<Clock, Duration>& tp);

template<typename Clock, typename Duration = typename Clock::duration>
void to(const std::chrono::time_point<Clock, Duration>& tp, ros::Time& t);

}

#include "convert/ros/impl/rostime.hpp"

#endif
