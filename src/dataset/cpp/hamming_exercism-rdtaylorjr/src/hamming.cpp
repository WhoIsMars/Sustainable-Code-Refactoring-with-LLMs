#include "hamming.h"
#include <stdexcept>

namespace hamming {

std::size_t compute(std::string const& a, std::string const& b) {
    std::size_t hammingDistance = 0;
    
    if (a.length() != b.length())
        throw std::domain_error("Strings must be the same length");
    
    for (std::string::size_type i = 0; i < a.length(); ++i)
        if (a[i] != b[i])
            ++hammingDistance;

    return hammingDistance;
}

}  // namespace hamming
