#include "hamming.h"
#include <stdexcept>
#include <algorithm>

namespace hamming {

std::size_t compute(const std::string& a, const std::string& b) {
    if (a.length() != b.length())
        throw std::domain_error("Strings must be the same length");

    return std::transform_reduce(a.begin(), a.end(), b.begin(), std::size_t{0}, std::plus<>(), std::not_equal_to<>());
}

}  // namespace hamming