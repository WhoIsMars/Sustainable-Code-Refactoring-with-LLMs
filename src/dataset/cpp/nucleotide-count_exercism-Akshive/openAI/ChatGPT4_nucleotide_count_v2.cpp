#include "nucleotide_count.h"
#include <unordered_map>
#include <stdexcept>
#include <string>

using namespace std;

namespace dna
{
    counter::counter(const string& DNA) : DNA(DNA)
    {
        for (char c : DNA)
        {
            if (c != 'A' && c != 'G' && c != 'T' && c != 'C')
                throw std::invalid_argument("Invalid Argument");
        }
    }

    unordered_map<char, int> counter::nucleotide_counts() const
    {
        unordered_map<char, int> ans = {{'A', 0}, {'T', 0}, {'C', 0}, {'G', 0}};
        for (char c : DNA)
        {
            ans[c]++;
        }
        return ans;
    }

    int counter::count(char c) const
    {
        if (c != 'A' && c != 'G' && c != 'T' && c != 'C')
            throw std::invalid_argument("Invalid Argument");
        return count_if(DNA.begin(), DNA.end(), [c](char nucleotide) { return nucleotide == c; });
    }
}