#ifndef CONVERT_MATLAB_STD_MATLAB_STD_HPP
#define CONVERT_MATLAB_STD_MATLAB_STD_HPP

#include <cppbox/time.hpp>
#include <mex.hpp>
#include <type_traits>
#include <vector>

namespace convert {

template<typename Scalar>
void to(const matlab::data::TypedArray<Scalar>& array, Scalar& scalar);

template<typename Scalar>
void to(const matlab::data::TypedArray<Scalar>& array, std::vector<Scalar>& vector);

template<cppbox::IsTimePoint TimePoint>
void to(const matlab::data::Struct& time_struct, TimePoint& time);

template<cppbox::IsTimePoint TimePoint>
void to(const matlab::data::StructArray& times_struct_array, std::vector<TimePoint>& times);

template<typename Scalar>
std::enable_if_t<std::is_fundamental_v<Scalar>, matlab::data::TypedArray<Scalar>> to_array(const Scalar& scalar,
        matlab::data::ArrayFactory& factory);

template<typename Scalar>
matlab::data::TypedArray<Scalar> to_array(const std::vector<Scalar>& vector, matlab::data::ArrayFactory& factory);

template<typename T>
matlab::data::CellArray to_cells_of_arrays(const std::vector<T>& vector, matlab::data::ArrayFactory& factory);

template<cppbox::IsTimePoint TimePoint>
matlab::data::StructArray to_struct_array(const TimePoint& time, matlab::data::ArrayFactory& factory);

template<cppbox::IsTimePoint TimePoint>
matlab::data::StructArray to_struct_array(const std::vector<TimePoint>& times, matlab::data::ArrayFactory& factory);

}

#include "convert/matlab_std/impl/matlab_std.hpp"

#endif
