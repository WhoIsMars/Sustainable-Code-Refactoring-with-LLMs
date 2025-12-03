#include "nucleotide_count.h"
#include <array>

namespace dna
{

    counter::counter(const std::string dna) : m_dna(dna)
    {
        for (char nucleotide : dna)
            check_nucleotide_validity(nucleotide);
    }

    std::map<char, int> counter::nucleotide_counts(void) const
    {
        std::map<char, int> result{{'A', 0}, {'T', 0}, {'G', 0}, {'C', 0}};
        for (char c : m_dna)
            result[c]++;
        return result;
    }

    unsigned int counter::count(char nucleotide) const
    {
        check_nucleotide_validity(nucleotide);
        return std::count(m_dna.begin(), m_dna.end(), nucleotide);
    }

    void counter::check_nucleotide_validity(char nucleotide) const
    {
        static const std::array<char, 4> valid_nucleotides{'A', 'T', 'G', 'C'};
        if (std::find(valid_nucleotides.begin(), valid_nucleotides.end(), nucleotide) == valid_nucleotides.end())
            throw std::invalid_argument("Nucleotides are 'A', 'T', 'G' or 'C'.");
    }

}