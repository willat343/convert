#include "convert/ros/ros.hpp"

#include <gtest/gtest.h>

#include "convert/test/helpers.hpp"
#include "convert/test/instances.hpp"

TEST(rostime_chrono, to_from) {
    convert::test::test_to_from_eq<ros::Time, std::chrono::time_point<std::chrono::steady_clock>>(
            std::chrono::time_point<std::chrono::steady_clock>());
    const auto instances = convert::test::test_instances<std::chrono::time_point<std::chrono::steady_clock>, 100>();
    for (unsigned int i = 0; i < instances.size(); ++i) {
        convert::test::test_to_from_eq<ros::Time>(instances[i]);
    }
}
