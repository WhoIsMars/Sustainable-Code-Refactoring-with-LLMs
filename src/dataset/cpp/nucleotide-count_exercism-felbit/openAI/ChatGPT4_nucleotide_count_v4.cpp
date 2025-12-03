#include "nucleotide_count.h"
#include <array>

namespace dna
{

    counter::counter(const std::string& dna) : m_counts{{0, 0, 0, 0}}
    {
        for (char nucleotide : dna)
        {
            check_nucleotide_validity(nucleotide);
            m_counts[m_nucleotide_map.at(nucleotide)]++;
        }
        m_dna = dna;
    }

    std::map<char, int> counter::nucleotide_counts(void) const
    {
        return {
            {'A', m_counts[0]},
            {'T', m_counts[1]},
            {'G', m_counts[2]},
            {'C', m_counts[3]}
        };
    }

    unsigned int counter::count(char nucleotide) const
    {
        check_nucleotide_validity(nucleotide);
        return m_counts[m_nucleotide_map.at(nucleotide)];
    }

    void counter::check_nucleotide_validity(char nucleotide) const
    {
        if (m_nucleotide_map.find(nucleotide) == m_nucleotide_map.end())
            throw std::invalid_argument("Nucleotides are 'A', 'T', 'G' or 'C'.");
    }

    const std::map<char, int> counter::m_nucleotide_map = {
        {'A', 0}, {'T', 1}, {'G', 2}, {'C', 3}
    };

}