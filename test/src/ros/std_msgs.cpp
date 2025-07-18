#include <gtest/gtest.h>

#include "convert/ros/ros.hpp"
// conversion helpers
#include "convert/convert_helpers.hpp"
#include "convert/test/instances.hpp"

TEST(header, to_from) {
    // seq not set so stays at 0
    EXPECT_EQ(std_msgs::Header(),
            (convert::to<std_msgs::Header, std::chrono::time_point<std::chrono::steady_clock>, std::string>(
                    std::chrono::time_point<std::chrono::steady_clock>(), "")));
    const auto instances = convert::test::test_instances<std_msgs::Header, 100>();
    for (unsigned int i = 0; i < instances.size(); ++i) {
        std::chrono::time_point<std::chrono::steady_clock> mid1;
        std::string mid2;
        convert::to(instances[i], mid1, mid2);
        std_msgs::Header out;
        convert::to(mid1, mid2, out);
        EXPECT_EQ(instances[i].stamp, out.stamp);
        EXPECT_EQ(instances[i].frame_id, out.frame_id);
    }
}
