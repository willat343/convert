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

}

#endif
