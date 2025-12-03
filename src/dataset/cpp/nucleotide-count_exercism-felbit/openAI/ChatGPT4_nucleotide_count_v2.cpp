#include "nucleotide_count.h"
#include <array>

namespace dna
{

    counter::counter(const std::string& dna) : m_counts{{0, 0, 0, 0}}
    {
        for (char nucleotide : dna)
        {
            check_nucleotide_validity(nucleotide);
            m_counts[nucleotide_to_index(nucleotide)]++;
        }
        m_dna = dna;
    }

    std::map<char, int> counter::nucleotide_counts(void) const
    {
        return {{'A', m_counts[0]}, {'T', m_counts[1]}, {'G', m_counts[2]}, {'C', m_counts[3]}};
    }

    unsigned int counter::count(char nucleotide) const
    {
        check_nucleotide_validity(nucleotide);
        return m_counts[nucleotide_to_index(nucleotide)];
    }

    void counter::check_nucleotide_validity(char nucleotide) const
    {
        if (nucleotide != 'A' && nucleotide != 'T' && nucleotide != 'G' && nucleotide != 'C')
            throw std::invalid_argument("Nucleotides are 'A', 'T', 'G' or 'C'.");
    }

    int counter::nucleotide_to_index(char nucleotide) const
    {
        switch (nucleotide)
        {
            case 'A': return 0;
            case 'T': return 1;
            case 'G': return 2;
            case 'C': return 3;
            default: throw std::invalid_argument("Invalid nucleotide.");
        }
    }

}