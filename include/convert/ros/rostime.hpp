#ifndef CONVERT_ROS_ROSTIME_HPP
#define CONVERT_ROS_ROSTIME_HPP

#include <ros/time.h>

#include <chrono>
#include <cppbox/time.hpp>

namespace convert {

template<cppbox::IsTimePoint TimePoint>
void to(const ros::Time& t, TimePoint& tp);

template<cppbox::IsTimePoint TimePoint>
void to(const TimePoint& tp, ros::Time& t);

}

#include "convert/ros/impl/rostime.hpp"

#endif
