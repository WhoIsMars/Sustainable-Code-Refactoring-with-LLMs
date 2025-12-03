#include "nucleotide_count.h"

namespace dna
{

    counter::counter(const std::string& dna) : m_dna(dna) {
        for (char nucleotide : dna)
            check_nucleotide_validity(nucleotide);
    }

    std::map<char, int> counter::nucleotide_counts(void) const
    {
        std::map<char, int> result;
        
        // Initialize all nucleotides to 0
        for (char c : m_nucleotides)
            result[c] = 0;
        
        // Count all nucleotides in a single pass
        for (char c : m_dna)
            result[c]++;

        return result;
    }

    unsigned int counter::count(char nucleotide) const
    {
        check_nucleotide_validity(nucleotide);

        unsigned int result = 0;
        for (char c : m_dna)
            if (c == nucleotide)
                result++;
        
        return result;
    }

    void counter::check_nucleotide_validity(char nucleotide) const
    {
        if (m_nucleotides.find(nucleotide) == m_nucleotides.end())
            throw std::invalid_argument("Nucleotides are 'A', 'T', 'G' or 'C'.");
    }

}