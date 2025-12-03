#include "nucleotide_count.h"
#include <stdexcept>
#include <string>
#include <map>
#include <array>

namespace dna
{
    dna::counter::counter(const std::string& DNA) : DNA(DNA)
    {
        for (char c : DNA)
        {
            if (c != 'A' && c != 'G' && c != 'T' && c != 'C')
                throw std::invalid_argument("Invalid Argument");
        }
    }

    std::map<char, int> dna::counter::nucleotide_counts() const
    {
        std::array<int, 4> counts = {0, 0, 0, 0};
        
        for (char c : DNA)
        {
            switch (c)
            {
                case 'A': counts[0]++; break;
                case 'C': counts[1]++; break;
                case 'G': counts[2]++; break;
                case 'T': counts[3]++; break;
            }
        }
        
        return {{'A', counts[0]}, {'C', counts[1]}, {'G', counts[2]}, {'T', counts[3]}};
    }

    int dna::counter::count(char c) const
    {
        if (c != 'A' && c != 'G' && c != 'T' && c != 'C')
            throw std::invalid_argument("Invalid Argument");
        
        int count = 0;
        for (char nucleotide : DNA)
        {
            if (nucleotide == c) count++;
        }
        return count;
    }
}