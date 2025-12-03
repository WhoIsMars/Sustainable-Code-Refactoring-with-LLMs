#include "nucleotide_count.h"
#include <unordered_map>
#include <stdexcept>
#include <string>

namespace dna
{
    counter::counter(const std::string& DNA) : DNA(DNA)
    {
        for (char c : DNA)
        {
            if (c != 'A' && c != 'G' && c != 'T' && c != 'C')
                throw std::invalid_argument("Invalid Argument");
        }
    }

    std::map<char, int> counter::nucleotide_counts() const
    {
        std::map<char, int> ans{{'A', 0}, {'T', 0}, {'C', 0}, {'G', 0}};
        for (char c : DNA)
        {
            ++ans[c];
        }
        return ans;
    }

    int counter::count(char c) const
    {
        if (c != 'A' && c != 'G' && c != 'T' && c != 'C')
            throw std::invalid_argument("Invalid Argument");
        return std::count(DNA.begin(), DNA.end(), c);
    }
}