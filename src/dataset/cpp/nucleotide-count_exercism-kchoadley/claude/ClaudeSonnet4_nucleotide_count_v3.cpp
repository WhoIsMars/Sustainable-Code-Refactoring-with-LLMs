#include "nucleotide_count.h"
#include <stdexcept>
#include <string_view>

namespace dna {
    
    counter::counter(std::string strand) : nucleotides{{'A', 0}, {'C', 0}, {'G', 0}, {'T', 0}}
    {
        for (char c : strand) 
        {
            auto it = nucleotides.find(c);
            if (it == nucleotides.end())
                throw std::invalid_argument(std::string("Invalid argument ") + c);
            
            ++it->second;
        }
    }
    
    int counter::count(const char& c) const
    {
        auto it = nucleotides.find(c);
        if (it == nucleotides.end())
            throw std::invalid_argument(std::string("Invalid argument ") + c);
            
        return it->second;
    }
    
    std::map<char, int> counter::nucleotide_counts() const
    {
        return nucleotides;
    }

}