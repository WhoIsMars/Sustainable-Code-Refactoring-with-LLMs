#include "hamming.h"

#include <string>
#include <stdexcept>

namespace hamming {

    int compute(const std::string& a, const std::string& b)
    {
        if(a.length() != b.length()) 
            throw std::domain_error("Nucleotides are of different length.");

        int point_mutations = 0;
        const std::size_t len = a.length();
        for(std::size_t i = 0; i < len; ++i) 
            if(a[i] != b[i]) ++point_mutations;
        return point_mutations;
    }

}