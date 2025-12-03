#include "nucleotide_count.h"
#include <stdexcept>
#include <algorithm>

namespace dna {

    counter::counter(std::string strand) : nucleotides({{'A', 0}, {'C', 0}, {'G', 0}, {'T', 0}}) {
        for (char c : strand) {
            if (nucleotides.find(c) == nucleotides.end()) {
                throw std::invalid_argument("Invalid argument");
            }
            nucleotides[c]++;
        }
    }

    int counter::count(const char& c) const {
        if (nucleotides.find(c) == nucleotides.end()) {
            throw std::invalid_argument("Invalid argument");
        }
        return nucleotides.at(c);
    }

    std::map<char, int> counter::nucleotide_counts() const {
        return nucleotides;
    }

}