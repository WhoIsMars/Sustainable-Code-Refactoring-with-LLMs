#include "nucleotide_count.h"
#include <stdexcept>
#include <string>
#include <map>

namespace dna
{
    dna::counter::counter(std::string DNA)
    {
        for (char c : DNA)
        {
            if (c != 'A' && c != 'G' && c != 'T' && c != 'C')
                throw std::invalid_argument("Invalid Argument");
        }
        this->DNA = std::move(DNA);
    }
    
    std::map<char, int> dna::counter::nucleotide_counts() const
    {
        std::map<char, int> ans{{'A', 0}, {'T', 0}, {'C', 0}, {'G', 0}};
        for (char c : this->DNA)
        {
            ans[c]++;
        }
        return ans;
    }
    
    int dna::counter::count(char c) const
    {
        if (c != 'A' && c != 'G' && c != 'T' && c != 'C')
            throw std::invalid_argument("Invalid Argument");
        
        int ans = 0;
        for (char nucleotide : this->DNA)
        {
            if (nucleotide == c) ans++;
        }
        return ans;
    }
}