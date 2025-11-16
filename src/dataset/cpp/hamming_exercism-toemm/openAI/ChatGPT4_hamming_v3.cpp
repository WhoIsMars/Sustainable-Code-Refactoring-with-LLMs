#include "hamming.h"

#include <stdexcept>
#include <algorithm>

namespace hamming {

int compute(const std::string& one, const std::string& two) {
    if (one.size() != two.size()) throw std::domain_error("different sizes.");

    return std::transform_reduce(one.begin(), one.end(), two.begin(), 0, std::plus<>(), 
                                 [](char a, char b) { return a != b; });
}

}  // namespace hamming