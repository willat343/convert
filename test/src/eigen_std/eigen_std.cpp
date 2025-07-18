#include "convert/eigen_std/eigen_std.hpp"

#include <gtest/gtest.h>

#include "convert/test/helpers.hpp"
#include "convert/test/instances.hpp"

TEST(vectorXd_vectord, to_from) {
    convert::test::test_to_from_eq<Eigen::VectorXd>(std::vector<double>());
    std::vector<double> v{{1.0, 2.0, 3.0}};
    convert::test::test_to_from_eq<Eigen::VectorXd>(v);
}

TEST(vector3d_arrayd3, to_from) {
    convert::test::test_to_from_eq<Eigen::Vector3d>(std::array<double, 3>({1.0, 2.0, 3.0}));
    auto instances = convert::test::test_instances<std::array<double, 3>, 100>();
    for (unsigned int i = 0; i < instances.size(); ++i) {
        convert::test::test_to_from_eq<Eigen::Vector3d>(instances[i]);
    }
}
