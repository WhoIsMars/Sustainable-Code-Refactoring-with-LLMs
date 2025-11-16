#include "hamming.h"

#include <string>
#include <stdexcept>
#include <algorithm>

namespace hamming {

    int compute(const std::string& a, const std::string& b)
    {
        if (a.size() != b.size()) 
            throw std::domain_error("Nucleotides are of different length.");

        return std::transform_reduce(a.begin(), a.end(), b.begin(), 0, std::plus<>(), std::not_equal_to<>());
    }

}