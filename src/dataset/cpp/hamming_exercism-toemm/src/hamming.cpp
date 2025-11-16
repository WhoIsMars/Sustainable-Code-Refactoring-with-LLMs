#include "hamming.h"

#include <stdexcept>

namespace hamming {

int compute(const std::string& one, const std::string& two) {

    if (one.size() != two.size()) throw std::domain_error("different sizes.");

    int hamming_ctr{};

    for (std::size_t i{}; i < one.size(); i++) {
        if (one[i] != two[i]) hamming_ctr++;

    }
    return hamming_ctr;

}




}  // namespace hamming
