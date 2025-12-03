#include "hamming.h"

#include <string>
#include <stdexcept>
#include <algorithm>

namespace hamming {

    int compute(std::string a, std::string b)
    {
        if(a.length() != b.length()) 
            throw std::domain_error("Nucleotides are of different length.");

        int point_mutations = 0;
        size_t length = a.length();

        // Early exit optimization
        if (length == 0) return 0;

        for(size_t i = 0; i < length; ++i) {
            if(a[i] != b[i]) {
                ++point_mutations;
            }
        }
        return point_mutations;
    }

}