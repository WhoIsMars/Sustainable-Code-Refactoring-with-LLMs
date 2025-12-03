#include "nucleotide_count.h"
#include <stdexcept>

namespace dna {
    
    counter::counter(const std::string& strand) : nucleotides{{'A', 0}, {'C', 0}, {'G', 0}, {'T', 0}}
    {
        for (char c : strand) {
            switch (c) {
                case 'A':
                case 'C':
                case 'G':
                case 'T':
                    ++nucleotides[c];
                    break;
                default:
                    throw std::invalid_argument(std::string("Invalid argument ") + c);
            }
        }
    }
    
    int counter::count(const char& c) const
    {
        switch (c) {
            case 'A':
            case 'C':
            case 'G':
            case 'T':
                return nucleotides.at(c);
            default:
                throw std::invalid_argument(std::string("Invalid argument ") + c);
        }
    }
    
    std::map<char, int> counter::nucleotide_counts() const
    {
        return nucleotides;
    }

}