#include "convert/eigen_nlohmann_json/eigen_nlohmann_json.hpp"

#include <gtest/gtest.h>

TEST(json_matrix, to_from_2x4d) {
    const Eigen::Matrix<double, 2, 4> in{{1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}};
    const nlohmann::json j = in;
    const Eigen::Matrix<double, 2, 4> out = j.get<Eigen::Matrix<double, 2, 4>>();
    EXPECT_EQ(in, out);
}

TEST(json_matrix, to_from_2x4Xd) {
    const Eigen::MatrixXd in{{1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}};
    const nlohmann::json j = in;
    const Eigen::MatrixXd out = j.get<Eigen::MatrixXd>();
    EXPECT_EQ(in, out);
}

TEST(json_quaternion, to_from_d) {
    const Eigen::Quaterniond in = Eigen::Quaterniond(1.0, 2.0, 3.0, 4.0).normalized();
    const nlohmann::json j = in;
    const Eigen::Quaterniond out = j.get<Eigen::Quaterniond>();
    EXPECT_EQ(in, out);
}

TEST(json_quaternion, to_from_f) {
    const Eigen::Quaternionf in = Eigen::Quaternionf(1.0f, 2.0f, 3.0f, 4.0f).normalized();
    const nlohmann::json j = in;
    const Eigen::Quaternionf out = j.get<Eigen::Quaternionf>();
    EXPECT_EQ(in, out);
}

TEST(json_rotation2D, to_from_d) {
    const Eigen::Rotation2Dd in(1.0);
    const nlohmann::json j = in;
    const Eigen::Rotation2Dd out = j.get<Eigen::Rotation2Dd>();
    EXPECT_TRUE(in.isApprox(out));
}

TEST(json_rotation2D, to_from_f) {
    const Eigen::Rotation2Df in(1.0f);
    const nlohmann::json j = in;
    const Eigen::Rotation2Df out = j.get<Eigen::Rotation2Df>();
    EXPECT_TRUE(in.isApprox(out));
}

TEST(json_translation2D, to_from_d) {
    const Eigen::Translation2d in(1.0, 2.0);
    const nlohmann::json j = in;
    const Eigen::Translation2d out = j.get<Eigen::Translation2d>();
    EXPECT_TRUE(in.isApprox(out));
}

TEST(json_translation2D, to_from_f) {
    const Eigen::Translation2f in(1.0f, 2.0f);
    const nlohmann::json j = in;
    const Eigen::Translation2f out = j.get<Eigen::Translation2f>();
    EXPECT_TRUE(in.isApprox(out));
}

TEST(json_translation3D, to_from_d) {
    const Eigen::Translation3d in(1.0, 2.0, 3.0);
    const nlohmann::json j = in;
    const Eigen::Translation3d out = j.get<Eigen::Translation3d>();
    EXPECT_TRUE(in.isApprox(out));
}

TEST(json_translation3D, to_from_f) {
    const Eigen::Translation3f in(1.0f, 2.0f, 3.0f);
    const nlohmann::json j = in;
    const Eigen::Translation3f out = j.get<Eigen::Translation3f>();
    EXPECT_TRUE(in.isApprox(out));
}

TEST(json_isometry2D, to_from_d) {
    const Eigen::Isometry2d in = Eigen::Translation2d(1.0, 2.0) * Eigen::Rotation2Dd(1.0);
    const nlohmann::json j = in;
    const Eigen::Isometry2d out = j.get<Eigen::Isometry2d>();
    EXPECT_TRUE(in.isApprox(out));
}

TEST(json_isometry2D, to_from_f) {
    const Eigen::Isometry2f in = Eigen::Translation2f(1.0f, 2.0f) * Eigen::Rotation2Df(1.0f);
    const nlohmann::json j = in;
    const Eigen::Isometry2f out = j.get<Eigen::Isometry2f>();
    EXPECT_TRUE(in.isApprox(out));
}

TEST(json_isometry3D, to_from_d) {
    const Eigen::Isometry3d in =
            Eigen::Translation3d(1.0, 2.0, 3.0) * Eigen::Quaterniond(1.0, 2.0, 3.0, 4.0).normalized();
    const nlohmann::json j = in;
    const Eigen::Isometry3d out = j.get<Eigen::Isometry3d>();
    EXPECT_TRUE(in.isApprox(out));
}

TEST(json_isometry3D, to_from_f) {
    const Eigen::Isometry3f in =
            Eigen::Translation3f(1.0f, 2.0f, 3.0f) * Eigen::Quaternionf(1.0f, 2.0f, 3.0f, 4.0f).normalized();
    const nlohmann::json j = in;
    const Eigen::Isometry3f out = j.get<Eigen::Isometry3f>();
    EXPECT_TRUE(in.isApprox(out));
}
