#include "nucleotide_count.h"
#include <stdexcept>
#include <algorithm>

namespace dna {

    counter::counter(std::string strand) : nucleotides{{'A', 0}, {'C', 0}, {'G', 0}, {'T', 0}}
    {
        for (char nucleotide : strand) {
            switch (nucleotide) {
                case 'A':
                case 'C':
                case 'G':
                case 'T':
                    nucleotides[nucleotide]++;
                    break;
                default:
                    throw std::invalid_argument("Invalid nucleotide: " + std::string(1, nucleotide));
            }
        }
    }

    int counter::count(const char& c) const
    {
        if (nucleotides.find(c) == nucleotides.end()) {
            throw std::invalid_argument("Invalid nucleotide: " + std::string(1, c));
        }
        return nucleotides.at(c);
    }

    std::map<char, int> counter::nucleotide_counts() const
    {
        return nucleotides;
    }

}