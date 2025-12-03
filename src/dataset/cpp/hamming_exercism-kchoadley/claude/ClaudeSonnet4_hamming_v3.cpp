#include "hamming.h"

#include <string>
#include <stdexcept>

namespace hamming {

    int compute(std::string a, std::string b)
    {
        const auto len = a.length();
        if(len != b.length()) 
            throw std::domain_error("Nucleotides are of different length.");

        int point_mutations = 0;
        const char* a_ptr = a.data();
        const char* b_ptr = b.data();
        
        for(std::size_t i = 0; i < len; ++i) 
            point_mutations += (a_ptr[i] != b_ptr[i]);
        
        return point_mutations;
    }

}