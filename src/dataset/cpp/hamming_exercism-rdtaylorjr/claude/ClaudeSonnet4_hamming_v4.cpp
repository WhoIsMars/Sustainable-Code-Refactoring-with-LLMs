#include "hamming.h"
#include <stdexcept>

namespace hamming {

std::size_t compute(std::string const& a, std::string const& b) {
    const std::size_t len = a.length();
    
    if (len != b.length())
        throw std::domain_error("Strings must be the same length");
    
    std::size_t hammingDistance = 0;
    const char* ptr_a = a.data();
    const char* ptr_b = b.data();
    
    for (std::size_t i = 0; i < len; ++i)
        hammingDistance += (ptr_a[i] != ptr_b[i]);

    return hammingDistance;
}

}  // namespace hamming