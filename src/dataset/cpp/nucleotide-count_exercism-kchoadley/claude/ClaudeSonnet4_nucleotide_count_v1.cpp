#include "nucleotide_count.h"
#include <stdexcept>

namespace dna {
    
    counter::counter(const std::string& strand)
    {
        nucleotides['A'] = 0;
        nucleotides['C'] = 0;
        nucleotides['G'] = 0;
        nucleotides['T'] = 0;
        
        for(char c : strand) 
        {
            switch(c) {
                case 'A':
                case 'C':
                case 'G':
                case 'T':
                    nucleotides[c]++;
                    break;
                default:
                    throw std::invalid_argument("Invalid argument");
            }
        }
    }
    
    int counter::count(const char& c) const
    {
        switch(c) {
            case 'A':
            case 'C':
            case 'G':
            case 'T':
                return nucleotides.at(c);
            default:
                throw std::invalid_argument("Invalid argument");
        }
    }
    
    std::map<char, int> counter::nucleotide_counts() const
    {
        return nucleotides;
    }

}