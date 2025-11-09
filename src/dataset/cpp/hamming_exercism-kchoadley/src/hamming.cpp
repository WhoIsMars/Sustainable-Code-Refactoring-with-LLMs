#include "hamming.h"

#include <string>
#include <stdexcept>

namespace hamming {

    int compute(std::string a, std::string b)
    {
        if(a.length() != b.length()) 
            throw std::domain_error("Nucleotides are of different length.");

        int point_mutations = 0;
        for(int i = 0; i < a.length(); i++) 
            if(a[i] != b[i]) point_mutations++;
        return point_mutations;
    }

}