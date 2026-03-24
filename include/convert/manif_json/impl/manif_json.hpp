#ifndef CONVERT_MANIF_NLOHMANN_JSON_IMPL_MANIF_NLOHMANN_JSON_HPP
#define CONVERT_MANIF_NLOHMANN_JSON_IMPL_MANIF_NLOHMANN_JSON_HPP

#include "convert/eigen_json/eigen_json.hpp"
#include "convert/manif_json/manif_json.hpp"

namespace nlohmann {

template<typename Scalar, unsigned int N>
void adl_serializer<manif::Rn<Scalar, N>>::to_json(json& j, const manif::Rn<Scalar, N>& m) {
    j = m.coeffs();
}

template<typename Scalar, unsigned int N>
void adl_serializer<manif::Rn<Scalar, N>>::from_json(const json& j, manif::Rn<Scalar, N>& m) {
    m = manif::Rn<Scalar, N>(j.get<Eigen::Vector<Scalar, N>>());
}

template<typename Scalar>
void adl_serializer<manif::SO2<Scalar>>::to_json(json& j, const manif::SO2<Scalar>& m) {
    j = Eigen::Rotation2D<Scalar>(m.angle());
}

template<typename Scalar>
void adl_serializer<manif::SO2<Scalar>>::from_json(const json& j, manif::SO2<Scalar>& m) {
    m = manif::SO2<Scalar>(j.get<Eigen::Rotation2D<Scalar>>().angle());
}

template<typename Scalar>
void adl_serializer<manif::SO3<Scalar>>::to_json(json& j, const manif::SO3<Scalar>& m) {
    j = m.quat();
}

template<typename Scalar>
void adl_serializer<manif::SO3<Scalar>>::from_json(const json& j, manif::SO3<Scalar>& m) {
    m = manif::SO3<Scalar>(j.get<Eigen::Quaternion<Scalar>>());
}

template<typename Scalar>
void adl_serializer<manif::SE2<Scalar>>::to_json(json& j, const manif::SE2<Scalar>& m) {
    j["position"] = Eigen::Translation<Scalar, 2>(m.translation());
    j["orientation"] = Eigen::Rotation2D<Scalar>(m.rotation());
}

template<typename Scalar>
void adl_serializer<manif::SE2<Scalar>>::from_json(const json& j, manif::SE2<Scalar>& m) {
    m = manif::SE2<Scalar>(
            j["position"].get<Eigen::Translation<Scalar, 2>>() * j["orientation"].get<Eigen::Rotation2D<Scalar>>());
}

template<typename Scalar>
void adl_serializer<manif::SE3<Scalar>>::to_json(json& j, const manif::SE3<Scalar>& m) {
    j["position"] = Eigen::Translation<Scalar, 3>(m.translation());
    j["orientation"] = m.quat();
}

template<typename Scalar>
void adl_serializer<manif::SE3<Scalar>>::from_json(const json& j, manif::SE3<Scalar>& m) {
    m = manif::SE3<Scalar>(
            j["position"].get<Eigen::Translation<Scalar, 3>>() * j["orientation"].get<Eigen::Quaternion<Scalar>>());
}

}

#endif
