#include "hamming.h"

#include <stdexcept>

namespace hamming {

int compute(const std::string& one, const std::string& two) {
    if (one.size() != two.size()) throw std::domain_error("different sizes.");

    int hamming_ctr = 0;
    const std::size_t size = one.size();
    
    for (std::size_t i = 0; i < size; ++i) {
        hamming_ctr += (one[i] != two[i]);
    }
    
    return hamming_ctr;
}

}  // namespace hamming