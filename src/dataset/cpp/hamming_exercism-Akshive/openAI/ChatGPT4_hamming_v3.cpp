#include "hamming.h"
#include <stdexcept>
#include <string>

namespace hamming {
    int compute(const std::string& strand1, const std::string& strand2) {
        if (strand1.size() != strand2.size()) {
            throw std::domain_error("Invalid Arguments");
        }
        return std::inner_product(strand1.begin(), strand1.end(), strand2.begin(), 0,
                                  std::plus<>(), std::not_equal_to<>());
    }
}