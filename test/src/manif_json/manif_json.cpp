#include <gtest/gtest.h>

#include "convert/manif_json/manif_json.hpp"

TEST(json_r1, to_from_d) {
    const manif::R1d in(Eigen::Matrix<double, 1, 1>(1.0));
    const nlohmann::json j = in;
    const manif::R1d out = j.get<manif::R1d>();
    EXPECT_EQ(in, out);
}

TEST(json_r1, to_from_f) {
    const manif::R1f in(Eigen::Matrix<float, 1, 1>(1.0f));
    const nlohmann::json j = in;
    const manif::R1f out = j.get<manif::R1f>();
    EXPECT_EQ(in, out);
}

TEST(json_r2, to_from_d) {
    const manif::R2d in(Eigen::Vector2d(1.0, 2.0));
    const nlohmann::json j = in;
    const manif::R2d out = j.get<manif::R2d>();
    EXPECT_EQ(in, out);
}

TEST(json_r2, to_from_f) {
    const manif::R2f in(Eigen::Vector2f(1.0f, 2.0f));
    const nlohmann::json j = in;
    const manif::R2f out = j.get<manif::R2f>();
    EXPECT_EQ(in, out);
}

TEST(json_r3, to_from_d) {
    const manif::R3d in(Eigen::Vector3d(1.0, 2.0, 3.0));
    const nlohmann::json j = in;
    const manif::R3d out = j.get<manif::R3d>();
    EXPECT_EQ(in, out);
}

TEST(json_r3, to_from_f) {
    const manif::R3f in(Eigen::Vector3f(1.0f, 2.0f, 3.0f));
    const nlohmann::json j = in;
    const manif::R3f out = j.get<manif::R3f>();
    EXPECT_EQ(in, out);
}

TEST(json_r4, to_from_d) {
    const manif::R4d in(Eigen::Vector4d(1.0, 2.0, 3.0, 4.0));
    const nlohmann::json j = in;
    const manif::R4d out = j.get<manif::R4d>();
    EXPECT_EQ(in, out);
}

TEST(json_r4, to_from_f) {
    const manif::R4f in(Eigen::Vector4f(1.0f, 2.0f, 3.0f, 4.0f));
    const nlohmann::json j = in;
    const manif::R4f out = j.get<manif::R4f>();
    EXPECT_EQ(in, out);
}

TEST(json_so2, to_from_d) {
    const manif::SO2d in(1.0);
    const nlohmann::json j = in;
    const manif::SO2d out = j.get<manif::SO2d>();
    EXPECT_EQ(in, out);
}

TEST(json_so2, to_from_f) {
    const manif::SO2f in(1.0f);
    const nlohmann::json j = in;
    const manif::SO2f out = j.get<manif::SO2f>();
    EXPECT_EQ(in, out);
}

TEST(json_so3, to_from_d) {
    const manif::SO3d in(Eigen::Quaterniond(1.0, 2.0, 3.0, 4.0).normalized());
    const nlohmann::json j = in;
    const manif::SO3d out = j.get<manif::SO3d>();
    EXPECT_EQ(in, out);
}

TEST(json_so3, to_from_f) {
    const manif::SO3f in(Eigen::Quaternionf(1.0f, 2.0f, 3.0f, 4.0f).normalized());
    const nlohmann::json j = in;
    const manif::SO3f out = j.get<manif::SO3f>();
    EXPECT_EQ(in, out);
}

TEST(json_se2, to_from_d) {
    const manif::SE2d in(Eigen::Translation2d(1.0, 2.0) * Eigen::Rotation2Dd(1.0));
    const nlohmann::json j = in;
    const manif::SE2d out = j.get<manif::SE2d>();
    EXPECT_EQ(in, out);
}

TEST(json_se2, to_from_f) {
    const manif::SE2f in(Eigen::Translation2f(1.0f, 2.0f) * Eigen::Rotation2Df(1.0f));
    const nlohmann::json j = in;
    const manif::SE2f out = j.get<manif::SE2f>();
    EXPECT_EQ(in, out);
}

TEST(json_se3, to_from_d) {
    const manif::SE3d in(Eigen::Translation3d(1.0, 2.0, 3.0) * Eigen::Quaterniond(1.0, 2.0, 3.0, 4.0).normalized());
    const nlohmann::json j = in;
    const manif::SE3d out = j.get<manif::SE3d>();
    EXPECT_EQ(in, out);
}

TEST(json_se3, to_from_f) {
    const manif::SE3f in(
            Eigen::Translation3f(1.0f, 2.0f, 3.0f) * Eigen::Quaternionf(1.0f, 2.0f, 3.0f, 4.0f).normalized());
    const nlohmann::json j = in;
    const manif::SE3f out = j.get<manif::SE3f>();
    EXPECT_EQ(in, out);
}
