#include "nucleotide_count.h"
#include <stdexcept>

namespace dna {
    
    counter::counter(std::string strand)
    {
        for(int i = 0; i < strand.length(); i++) 
        {
            if(nucleotides.find(strand[i]) == nucleotides.end())
                throw std::invalid_argument("Invalid argument " + strand[i]);

            nucleotides[strand[i]]++;
        }
    }
    int counter::count(const char& c) const
    {
        if(nucleotides.find(c) == nucleotides.end())
            throw std::invalid_argument("Invalid argument " + c);
            
        return nucleotides.at(c);
    }
    
    std::map<char, int> counter::nucleotide_counts() const
    {
        return nucleotides;
    }

}
