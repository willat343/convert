#include "convert/eigen_std/eigen_std.hpp"

namespace convert {

template void to<double>(const std::vector<double>&, Eigen::VectorXd&);
template void to<double>(const Eigen::VectorXd&, std::vector<double>&);

}
