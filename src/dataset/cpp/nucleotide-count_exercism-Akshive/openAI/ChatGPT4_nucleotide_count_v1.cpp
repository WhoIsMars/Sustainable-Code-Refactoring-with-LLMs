#include "nucleotide_count.h"
#include <unordered_map>
#include <stdexcept>
#include <string>

using namespace std;

namespace dna
{
    counter::counter(string DNA) : DNA(move(DNA))
    {
        for (char c : this->DNA)
        {
            if (c != 'A' && c != 'G' && c != 'T' && c != 'C')
                throw invalid_argument("Invalid Argument");
        }
    }

    map<char, int> counter::nucleotide_counts() const
    {
        unordered_map<char, int> counts = {{'A', 0}, {'T', 0}, {'C', 0}, {'G', 0}};
        for (char c : DNA)
        {
            counts[c]++;
        }
        return map<char, int>(counts.begin(), counts.end());
    }

    int counter::count(char c) const
    {
        if (c != 'A' && c != 'G' && c != 'T' && c != 'C')
            throw invalid_argument("Invalid Argument");
        return count_if(DNA.begin(), DNA.end(), [c](char nucleotide) { return nucleotide == c; });
    }
}