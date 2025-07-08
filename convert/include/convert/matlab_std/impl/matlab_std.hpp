#ifndef CONVERT_MATLAB_STD_IMPL_MATLAB_STD_HPP
#define CONVERT_MATLAB_STD_IMPL_MATLAB_STD_HPP

#include <algorithm>

#include "convert/matlab_std/matlab_std.hpp"

namespace convert {

template<typename Scalar>
void to(const matlab::data::TypedArray<Scalar>& array, Scalar& scalar) {
    const matlab::data::ArrayDimensions dimensions = array.getDimensions();
    assert(dimensions.size() == 2 && dimensions[0] == 1 && dimensions[1] = 1);
    scalar = array[0];
}

template<typename Scalar>
void to(const matlab::data::TypedArray<Scalar>& array, std::vector<Scalar>& vector) {
    const matlab::data::ArrayDimensions dimensions = array.getDimensions();
    assert(dimensions.size() == 2 && dimensions[0] == 1);
    const std::size_t size = dimensions[1];
    vector.resize(size);
    std::copy(array.cbegin(), array.cend(), vector.begin());
}

template<cppbox::IsTimePoint TimePoint>
void to(const matlab::data::Struct& time_struct, TimePoint& time) {
    time = TimePoint{std::chrono::seconds(static_cast<int>(time_struct["seconds"][0])) +
                     std::chrono::nanoseconds(static_cast<int>(time_struct["nanoseconds"][0]))};
}

template<cppbox::IsTimePoint TimePoint>
void to(const matlab::data::StructArray& times_struct_array, std::vector<TimePoint>& times) {
    const std::size_t size = times_struct_array.getNumberOfElements();
    times.resize(size);
    for (std::size_t i = 0; i < size; ++i) {
        const matlab::data::Struct& time_struct = times_struct_array[i];
        to(time_struct, times[i]);
    }
}

template<typename Scalar>
inline std::enable_if_t<std::is_fundamental_v<Scalar>, matlab::data::TypedArray<Scalar>> to_array(const Scalar& scalar,
        matlab::data::ArrayFactory& factory) {
    return factory.createArray<Scalar>({1, 1}, {scalar});
}

template<typename Scalar>
matlab::data::TypedArray<Scalar> to_array(const std::vector<Scalar>& vector, matlab::data::ArrayFactory& factory) {
    const std::size_t size = vector.size();
    matlab::data::TypedArray<Scalar> array = factory.createArray<Scalar>({1, size});
    std::copy(vector.cbegin(), vector.cend(), array.begin());
    return array;
}

template<typename T>
matlab::data::CellArray to_cells_of_arrays(const std::vector<T>& vector, matlab::data::ArrayFactory& factory) {
    const std::size_t size = vector.size();
    matlab::data::CellArray cells = factory.createCellArray({1, size});
    std::transform(vector.cbegin(), vector.cend(), cells.begin(),
            [&factory](const T& t) { return to_array(t, factory); });
    return cells;
}

template<cppbox::IsTimePoint TimePoint>
matlab::data::StructArray to_struct_array(const TimePoint& time, matlab::data::ArrayFactory& factory) {
    matlab::data::StructArray time_array = factory.createStructArray({1, 1}, {{"seconds"}, {"nanoseconds"}});
    time_array[0]["seconds"] = convert::to_array(time.time_since_epoch() / std::chrono::seconds(1), factory);
    time_array[0]["nanoseconds"] =
            convert::to_array((time.time_since_epoch() % std::chrono::seconds(1)).count(), factory);
    return time_array;
}

template<cppbox::IsTimePoint TimePoint>
matlab::data::StructArray to_struct_array(const std::vector<TimePoint>& times, matlab::data::ArrayFactory& factory) {
    matlab::data::StructArray times_array =
            factory.createStructArray({1, times.size()}, {{"seconds"}, {"nanoseconds"}});
    for (std::size_t i = 0; i < times.size(); ++i) {
        times_array[i]["seconds"] = convert::to_array(times[i].time_since_epoch() / std::chrono::seconds(1), factory);
        times_array[i]["nanoseconds"] =
                convert::to_array((times[i].time_since_epoch() % std::chrono::seconds(1)).count(), factory);
    }
    return times_array;
}

}

#endif
