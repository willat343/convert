#include "convert/matlab_std/matlab_std.hpp"

namespace convert {

template void to<double>(const matlab::data::TypedArray<double>&, double&);
template void to<double>(const matlab::data::TypedArray<double>&, std::vector<double>&);
template void to<std::chrono::time_point<std::chrono::steady_clock>>(const matlab::data::Struct&,
        std::chrono::time_point<std::chrono::steady_clock>&);
template void to<std::chrono::time_point<std::chrono::system_clock>>(const matlab::data::Struct&,
        std::chrono::time_point<std::chrono::system_clock>&);
template void to<std::chrono::time_point<std::chrono::system_clock>>(const matlab::data::StructArray&,
        std::vector<std::chrono::time_point<std::chrono::system_clock>>&);
template matlab::data::TypedArray<double> to_array<double>(const double&, matlab::data::ArrayFactory&);
template matlab::data::TypedArray<double> to_array<double>(const std::vector<double>&, matlab::data::ArrayFactory&);
template matlab::data::StructArray to_struct_array<std::chrono::time_point<std::chrono::system_clock>>(
        const std::chrono::time_point<std::chrono::system_clock>&, matlab::data::ArrayFactory&);
template matlab::data::StructArray to_struct_array<std::chrono::time_point<std::chrono::system_clock>>(
        const std::vector<std::chrono::time_point<std::chrono::system_clock>>&, matlab::data::ArrayFactory&);

}
