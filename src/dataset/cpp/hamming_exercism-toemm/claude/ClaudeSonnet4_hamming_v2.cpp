#include "hamming.h"

#include <stdexcept>

namespace hamming {

int compute(const std::string& one, const std::string& two) {
    const std::size_t size = one.size();
    if (size != two.size()) throw std::domain_error("different sizes.");

    int hamming_ctr = 0;
    const char* ptr1 = one.data();
    const char* ptr2 = two.data();

    for (std::size_t i = 0; i < size; ++i) {
        hamming_ctr += (ptr1[i] != ptr2[i]);
    }
    
    return hamming_ctr;
}

}  // namespace hamming