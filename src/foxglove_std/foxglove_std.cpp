#include "convert/foxglove_std/impl/foxglove_std.impl.hpp"

namespace convert {

template void to<std::chrono::steady_clock, std::chrono::steady_clock::duration>(
        const std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration>&,
        foxglove::schemas::Timestamp&);
template void to<std::chrono::system_clock, std::chrono::system_clock::duration>(
        const std::chrono::time_point<std::chrono::system_clock, std::chrono::system_clock::duration>&,
        foxglove::schemas::Timestamp&);

}
