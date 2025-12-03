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
        
        for (char c : m_nucleotides)
            result[c] = 0;
        
        for (char c : m_dna) {
            ++result[c];
        }

        return result;
    }

    unsigned int counter::count(char nucleotide) const
    {
        check_nucleotide_validity(nucleotide);

        return std::count(m_dna.begin(), m_dna.end(), nucleotide);
    }

    void counter::check_nucleotide_validity(char nucleotide) const
    {
        if (m_nucleotides.find(nucleotide) == std::string::npos)
            throw std::invalid_argument("Nucleotides are 'A', 'T', 'G' or 'C'.");
    }

}