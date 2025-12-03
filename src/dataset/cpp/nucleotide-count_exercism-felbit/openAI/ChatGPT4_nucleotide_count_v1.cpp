#include "nucleotide_count.h"
#include <array>

namespace dna
{

    counter::counter(const std::string dna) : m_dna(dna)
    {
        m_counts = {{'A', 0}, {'T', 0}, {'G', 0}, {'C', 0}};
        for (char nucleotide : dna)
        {
            check_nucleotide_validity(nucleotide);
            m_counts[nucleotide]++;
        }
    }

    std::map<char, int> counter::nucleotide_counts(void) const
    {
        return m_counts;
    }

    unsigned int counter::count(char nucleotide) const
    {
        check_nucleotide_validity(nucleotide);
        return m_counts.at(nucleotide);
    }

    void counter::check_nucleotide_validity(char nucleotide) const
    {
        if (m_counts.find(nucleotide) == m_counts.end())
            throw std::invalid_argument("Nucleotides are 'A', 'T', 'G' or 'C'.");
    }

}