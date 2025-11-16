#include "hamming.h"

#include <string>
#include <stdexcept>

namespace hamming {

    int compute(const std::string& a, const std::string& b)
    {
        if (a.size() != b.size()) 
            throw std::domain_error("Nucleotides are of different length.");

        int point_mutations = 0;
        for (size_t i = 0, n = a.size(); i < n; ++i) 
            point_mutations += (a[i] != b[i]);
        return point_mutations;
    }

}