#include "nucleotide_count.h"
#include <stdexcept>
#include <map>

using namespace std;

namespace dna
{
    dna::counter::counter(string DNA) : DNA(DNA)
    {
        for (char c : DNA)
        {
            if (c != 'A' && c != 'G' && c != 'T' && c != 'C')
            {
                throw std::invalid_argument("Invalid Argument");
            }
        }
    }

    map<char, int> dna::counter::nucleotide_counts() const
    {
        map<char, int> ans = {{'A', 0}, {'T', 0}, {'C', 0}, {'G', 0}};
        for (char c : DNA)
        {
            ans[c]++;
        }
        return ans;
    }

    int dna::counter::count(char c) const
    {
        if (c != 'A' && c != 'G' && c != 'T' && c != 'C')
        {
            throw std::invalid_argument("Invalid Argument");
        }
        int ans = 0;
        for (char nucleotide : DNA)
        {
            if (nucleotide == c)
            {
                ans++;
            }
        }
        return ans;
    }
}