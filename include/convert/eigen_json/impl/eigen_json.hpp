#ifndef CONVERT_EIGEN_NLOHMANN_JSON_IMPL_EIGEN_NLOHMANN_JSON_HPP
#define CONVERT_EIGEN_NLOHMANN_JSON_IMPL_EIGEN_NLOHMANN_JSON_HPP

#include "convert/eigen_json/eigen_json.hpp"

namespace nlohmann {

template<typename Scalar, int Rows, int Cols, int Options, int MaxRows, int MaxCols>
void adl_serializer<Eigen::Matrix<Scalar, Rows, Cols, Options, MaxRows, MaxCols>>::to_json(json& j,
        const Eigen::Matrix<Scalar, Rows, Cols, Options, MaxRows, MaxCols>& m) {
    j = json::array();
    for (int r = 0; r < m.rows(); ++r) {
        json row = json::array();
        for (int c = 0; c < m.cols(); ++c) {
            row.push_back(m(r, c));
        }
        j.push_back(std::move(row));
    }
}

template<typename Scalar, int Rows, int Cols, int Options, int MaxRows, int MaxCols>
void adl_serializer<Eigen::Matrix<Scalar, Rows, Cols, Options, MaxRows, MaxCols>>::from_json(const json& j,
        Eigen::Matrix<Scalar, Rows, Cols, Options, MaxRows, MaxCols>& m) {
    assert(j.is_array());
    const int rows = j.size();
    if (rows > 0 && j.at(0).is_array()) {
        // Nested array
        const int cols = j.at(0).size();
        m.resize(rows, cols);
        for (int r = 0; r < rows; ++r) {
            const json& row = j.at(r);
            assert(row.is_array());
            assert(row.size() == cols);
            for (int c = 0; c < cols; ++c) {
                m(r, c) = row.at(c).get<Scalar>();
            }
        }
    } else {
        // Flat array
        if constexpr (Cols == 1 || (Rows == Eigen::Dynamic && Cols == Eigen::Dynamic)) {
            // Column vector
            m.resize(rows, 1);
        } else {
            // Row vector
            m.resize(1, rows);
        }
        for (int r = 0; r < rows; ++r) {
            m(r) = j.at(r).get<Scalar>();
        }
    }
}

template<typename Scalar, int Options>
void adl_serializer<Eigen::Quaternion<Scalar, Options>>::to_json(json& j, const Eigen::Quaternion<Scalar, Options>& q) {
    j = json{{"w", q.w()}, {"x", q.x()}, {"y", q.y()}, {"z", q.z()}};
}

template<typename Scalar, int Options>
void adl_serializer<Eigen::Quaternion<Scalar, Options>>::from_json(const json& j,
        Eigen::Quaternion<Scalar, Options>& q) {
    q.w() = j.at("w").get<Scalar>();
    q.x() = j.at("x").get<Scalar>();
    q.y() = j.at("y").get<Scalar>();
    q.z() = j.at("z").get<Scalar>();
}

template<typename Scalar>
void adl_serializer<Eigen::Rotation2D<Scalar>>::to_json(json& j, const Eigen::Rotation2D<Scalar>& r) {
    j = json{{"angle", r.angle()}};
}

template<typename Scalar>
void adl_serializer<Eigen::Rotation2D<Scalar>>::from_json(const json& j, Eigen::Rotation2D<Scalar>& r) {
    r = Eigen::Rotation2D<Scalar>(j.at("angle").get<Scalar>());
}

template<typename Scalar, int Dim>
void adl_serializer<Eigen::Translation<Scalar, Dim>>::to_json(json& j, const Eigen::Translation<Scalar, Dim>& t) {
    j = json::object();
    if constexpr (Dim >= 1) {
        j["x"] = t.x();
    }
    if constexpr (Dim >= 2) {
        j["y"] = t.y();
    }
    if constexpr (Dim >= 3) {
        j["z"] = t.z();
    }
    if constexpr (Dim > 3) {
        for (int i = 3; i < Dim; ++i) {
            j["t" + std::to_string(i)] = t.translation().coeff(i);
        }
    }
}

template<typename Scalar, int Dim>
void adl_serializer<Eigen::Translation<Scalar, Dim>>::from_json(const json& j, Eigen::Translation<Scalar, Dim>& t) {
    if constexpr (Dim >= 1) {
        t.x() = j.at("x").get<Scalar>();
    }
    if constexpr (Dim >= 2) {
        t.y() = j.at("y").get<Scalar>();
    }
    if constexpr (Dim >= 3) {
        t.z() = j.at("z").get<Scalar>();
    }
    if constexpr (Dim > 3) {
        for (int i = 3; i < Dim; ++i) {
            t.translation().coeffRef(i) = j.at("t" + std::to_string(i)).get<Scalar>();
        }
    }
}

template<typename Scalar, int Dim, int Mode, int Options>
void adl_serializer<Eigen::Transform<Scalar, Dim, Mode, Options>>::to_json(json& j,
        const Eigen::Transform<Scalar, Dim, Mode, Options>& T) {
    static_assert(Dim == 2 || Dim == 3, "Dimension must be 2D or 3D.");
    j = json::object();
    j["translation"] = Eigen::Translation<Scalar, Dim>(T.translation());
    if constexpr (Dim == 2) {
        j["rotation"] = Eigen::Rotation2D<Scalar>(T.rotation());
    } else if constexpr (Dim == 3) {
        j["rotation"] = Eigen::Quaternion<Scalar>(T.rotation());
    }
}

template<typename Scalar, int Dim, int Mode, int Options>
void adl_serializer<Eigen::Transform<Scalar, Dim, Mode, Options>>::from_json(const json& j,
        Eigen::Transform<Scalar, Dim, Mode, Options>& T) {
    static_assert(Dim == 2 || Dim == 3, "Dimension must be 2D or 3D.");
    const Eigen::Translation<Scalar, Dim> t = j.at("translation").get<Eigen::Translation<Scalar, Dim>>();
    if constexpr (Dim == 2) {
        T = t * j.at("rotation").get<Eigen::Rotation2D<Scalar>>();
    } else if constexpr (Dim == 3) {
        T = t * j.at("rotation").get<Eigen::Quaternion<Scalar>>();
    }
}

}

#endif
