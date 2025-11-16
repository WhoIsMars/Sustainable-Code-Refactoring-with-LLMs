#include "hamming.h"
#include <stdexcept>
#include <string>

namespace hamming {

int compute(const std::string& strand1, const std::string& strand2) {
    if (strand1.size() != strand2.size())
        throw std::domain_error("Strands are not of same length");

    int distance = 0;
    for (size_t i = 0; i < strand1.size(); ++i) {
        distance += (strand1[i] != strand2[i]);
    }
    return distance;
}

}  // namespace hamming