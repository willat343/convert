#ifndef CONVERT_EIGEN_NLOHMANN_JSON_EIGEN_NLOHMANN_JSON_HPP
#define CONVERT_EIGEN_NLOHMANN_JSON_EIGEN_NLOHMANN_JSON_HPP

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <nlohmann/json.hpp>

namespace nlohmann {

/**
 * @brief Convert between json and a matrix.
 *
 * Example usage:
 * ```
 * const Eigen::MatrixXd in{{1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}};
 * const nlohmann::json j = in;
 * const Eigen::MatrixXd out = j.get<Eigen::MatrixXd>();
 * ```
 *
 * Json is stored as an array of arrays representing matrix rows.
 *
 * NOTE: Works for RowMajor and ColMajor, fixed and dynamic matrics.
 *
 * NOTE: Flat arrays during deserialization are acceptable as a special case, in which case the data is treated as a
 * vector. Differentiation between column or row vector is done by checking `Rows` and `Cols` in the (templated) result,
 * with column vector by default if ambiguous. This function never produces flat arrays during serialisation, but taking
 * the first array of the transpose of a column vector can produce the intended result:
 * ```
 * const Eigen::VectorXd in{{1.0, 2.0, 3.0, 4.0}};
 * const nlohmann::json j = in.transpose().eval();
 * const Eigen::MatrixXd out = j.at(0).get<Eigen::VectorXd>();
 * ```
 * Alternatively pass the transpose object itself does not call this serializer, and generates flat arrays:
 * ```
 * const Eigen::VectorXd in{{1.0, 2.0, 3.0, 4.0}};
 * const nlohmann::json j = in.transpose();
 * const Eigen::MatrixXd out = j.get<Eigen::VectorXd>();
 * ```
 *
 * @tparam Scalar
 * @tparam Rows
 * @tparam Cols
 * @tparam Options
 * @tparam MaxRows
 * @tparam MaxCols
 */
template<typename Scalar, int Rows, int Cols, int Options, int MaxRows, int MaxCols>
struct adl_serializer<Eigen::Matrix<Scalar, Rows, Cols, Options, MaxRows, MaxCols>> {
    /**
     * @brief Convert to json.
     *
     * @param j
     * @param m
     */
    static void to_json(json& j, const Eigen::Matrix<Scalar, Rows, Cols, Options, MaxRows, MaxCols>& m);

    /**
     * @brief Convert from json.
     *
     * @param j
     * @param m
     */
    static void from_json(const json& j, Eigen::Matrix<Scalar, Rows, Cols, Options, MaxRows, MaxCols>& m);
};

/**
 * @brief Convert between json and a quaternion.
 *
 * Example usage:
 * ```
 * const Eigen::Quaterniond in = Eigen::Quaterniond(1.0, 2.0, 3.0, 4.0).normalized();
 * const nlohmann::json j = in;
 * const Eigen::Quaterniond out = j.get<Eigen::Quaterniond>();
 * ```
 *
 * Json is stored as a `{"w":..., "x":..., "y":..., "z":...}` object.
 *
 * @tparam Scalar
 * @tparam Options
 */
template<typename Scalar, int Options>
struct adl_serializer<Eigen::Quaternion<Scalar, Options>> {
    /**
     * @brief Convert to json.
     *
     * @param j
     * @param q
     */
    static void to_json(json& j, const Eigen::Quaternion<Scalar, Options>& q);

    /**
     * @brief Convert from json.
     *
     * @param j
     * @param q
     */
    static void from_json(const json& j, Eigen::Quaternion<Scalar, Options>& q);
};

/**
 * @brief Convert between json and a 2D rotation.
 *
 * Example usage:
 * ```
 * const Eigen::Rotation2Dd in(1.0);
 * const nlohmann::json j = in;
 * const Eigen::Rotation2Dd out = j.get<Eigen::Rotation2Dd>();
 * ```
 *
 * Json is stored as a `{"angle":...}` object.
 *
 * @tparam Scalar
 */
template<typename Scalar>
struct adl_serializer<Eigen::Rotation2D<Scalar>> {
    /**
     * @brief Convert to json.
     *
     * @param j
     * @param r
     */
    static void to_json(json& j, const Eigen::Rotation2D<Scalar>& r);

    /**
     * @brief Convert from json.
     *
     * @param j
     * @param r
     */
    static void from_json(const json& j, Eigen::Rotation2D<Scalar>& r);
};

/**
 * @brief Convert between a json and a translation.
 *
 * Example usage:
 * ```
 * const Eigen::Translation3d in(1.0, 2.0, 3.0);
 * const nlohmann::json j = in;
 * const Eigen::Translation3d out = j.get<Eigen::Translation3d>();
 * ```
 *
 * Json is stored as a `{"x":..., "y":...}` (2D) or `{"x":..., "y":..., "z":...}` (3D) object.
 *
 * @tparam Scalar
 * @tparam Dim
 */
template<typename Scalar, int Dim>
struct adl_serializer<Eigen::Translation<Scalar, Dim>> {
    /**
     * @brief Convert to json.
     *
     * @param j
     * @param t
     */
    static void to_json(json& j, const Eigen::Translation<Scalar, Dim>& t);

    /**
     * @brief Convert from json.
     *
     * @param j
     * @param t
     */
    static void from_json(const json& j, Eigen::Translation<Scalar, Dim>& t);
};

/**
 * @brief Convert between a json and a transform.
 *
 * Example usage:
 * ```
 * const Eigen::Isometry3d in =
 *         Eigen::Translation3d(1.0, 2.0, 3.0) * Eigen::Quaterniond(1.0, 2.0, 3.0, 4.0).normalized();
 * const nlohmann::json j = in;
 * const Eigen::Isometry3d out = j.get<Eigen::Isometry3d>();
 * ```
 *
 * Json is stored as a `{"translation":..., "rotation":...}` object.
 *
 * @tparam Scalar
 * @tparam Dim
 * @tparam Mode
 * @tparam Options
 */
template<typename Scalar, int Dim, int Mode, int Options>
struct adl_serializer<Eigen::Transform<Scalar, Dim, Mode, Options>> {
    /**
     * @brief Convert to json.
     *
     * @param j
     * @param T
     */
    static void to_json(json& j, const Eigen::Transform<Scalar, Dim, Mode, Options>& T);

    /**
     * @brief Convert from json.
     *
     * @param j
     * @param t
     */
    static void from_json(const json& j, Eigen::Transform<Scalar, Dim, Mode, Options>& T);
};

}

#include "convert/eigen_nlohmann_json/impl/eigen_nlohmann_json.hpp"

#endif
