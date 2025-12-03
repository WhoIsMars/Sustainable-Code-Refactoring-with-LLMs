#include "nucleotide_count.h"
#include <stdexcept>
#include <algorithm>

namespace dna {
    
    counter::counter(std::string strand)
    {
        nucleotides['A'] = 0;
        nucleotides['C'] = 0;
        nucleotides['G'] = 0;
        nucleotides['T'] = 0;

        for (char nucleotide : strand) {
            switch (nucleotide) {
                case 'A':
                    nucleotides['A']++;
                    break;
                case 'C':
                    nucleotides['C']++;
                    break;
                case 'G':
                    nucleotides['G']++;
                    break;
                case 'T':
                    nucleotides['T']++;
                    break;
                default:
                    throw std::invalid_argument("Invalid argument");
            }
        }
    }
    int counter::count(const char& c) const
    {
        if (c != 'A' && c != 'C' && c != 'G' && c != 'T') {
            throw std::invalid_argument("Invalid argument");
        }
        return nucleotides.at(c);
    }
    
    std::map<char, int> counter::nucleotide_counts() const
    {
        return nucleotides;
    }

}