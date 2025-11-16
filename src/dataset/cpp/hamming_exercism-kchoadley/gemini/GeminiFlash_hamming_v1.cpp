#include "hamming.h"

#include <string>
#include <stdexcept>
#include <algorithm>

namespace hamming {

    int compute(std::string a, std::string b)
    {
        if (a.length() != b.length()) {
            throw std::domain_error("Nucleotides are of different length.");
        }

        int point_mutations = 0;
        for (size_t i = 0; i < a.length(); ++i) {
            point_mutations += (a[i] != b[i]);
        }
        return point_mutations;
    }

}