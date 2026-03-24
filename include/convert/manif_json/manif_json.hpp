#ifndef CONVERT_MANIF_NLOHMANN_JSON_MANIF_NLOHMANN_JSON_HPP
#define CONVERT_MANIF_NLOHMANN_JSON_MANIF_NLOHMANN_JSON_HPP

#include <manif/manif.h>

#include <nlohmann/json.hpp>

namespace nlohmann {

template<typename Scalar, unsigned int N>
struct adl_serializer<manif::Rn<Scalar, N>> {
    /**
     * @brief Convert to json.
     *
     * @param j
     * @param m
     */
    static void to_json(json& j, const manif::Rn<Scalar, N>& m);

    /**
     * @brief Convert from json.
     *
     * @param j
     * @param m
     */
    static void from_json(const json& j, manif::Rn<Scalar, N>& m);
};

template<typename Scalar>
struct adl_serializer<manif::SO2<Scalar>> {
    /**
     * @brief Convert to json.
     *
     * @param j
     * @param m
     */
    static void to_json(json& j, const manif::SO2<Scalar>& m);

    /**
     * @brief Convert from json.
     *
     * @param j
     * @param m
     */
    static void from_json(const json& j, manif::SO2<Scalar>& m);
};

template<typename Scalar>
struct adl_serializer<manif::SO3<Scalar>> {
    /**
     * @brief Convert to json.
     *
     * @param j
     * @param m
     */
    static void to_json(json& j, const manif::SO3<Scalar>& m);

    /**
     * @brief Convert from json.
     *
     * @param j
     * @param m
     */
    static void from_json(const json& j, manif::SO3<Scalar>& m);
};

template<typename Scalar>
struct adl_serializer<manif::SE2<Scalar>> {
    /**
     * @brief Convert to json.
     *
     * @param j
     * @param m
     */
    static void to_json(json& j, const manif::SE2<Scalar>& m);

    /**
     * @brief Convert from json.
     *
     * @param j
     * @param m
     */
    static void from_json(const json& j, manif::SE2<Scalar>& m);
};

template<typename Scalar>
struct adl_serializer<manif::SE3<Scalar>> {
    /**
     * @brief Convert to json.
     *
     * @param j
     * @param m
     */
    static void to_json(json& j, const manif::SE3<Scalar>& m);

    /**
     * @brief Convert from json.
     *
     * @param j
     * @param m
     */
    static void from_json(const json& j, manif::SE3<Scalar>& m);
};

}

#include "convert/manif_json/impl/manif_json.hpp"

#endif
