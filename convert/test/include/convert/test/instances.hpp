#ifndef CONVERT_TEST_INSTANCES_HPP
#define CONVERT_TEST_INSTANCES_HPP

#include <array>
#include <vector>

namespace convert::test {

template<typename T, int N>
std::array<T, N> test_instances(const unsigned int seed = 0);

template<typename T>
std::vector<T> test_instances(const std::size_t count, const unsigned int seed = 0);

template<typename T>
T random_instance() = delete;

}

#include "convert/test/impl/instances.hpp"

#endif
