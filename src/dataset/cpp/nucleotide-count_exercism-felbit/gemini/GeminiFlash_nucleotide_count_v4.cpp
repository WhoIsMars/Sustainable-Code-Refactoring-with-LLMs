#include "nucleotide_count.h"
#include <algorithm>

namespace dna
{

    counter::counter(const std::string dna) : m_dna(dna) {
        for (char nucleotide : m_dna)
            check_nucleotide_validity(nucleotide);
    }

    std::map<char, int> counter::nucleotide_counts(void) const
    {
        std::map<char, int> result;
        result['A'] = count('A');
        result['T'] = count('T');
        result['C'] = count('C');
        result['G'] = count('G');
        return result;
    }

    unsigned int counter::count(char nucleotide) const
    {
        check_nucleotide_validity(nucleotide);
        return std::count(m_dna.begin(), m_dna.end(), nucleotide);
    }

    void counter::check_nucleotide_validity(char nucleotide) const
    {
        if (nucleotide != 'A' && nucleotide != 'T' && nucleotide != 'C' && nucleotide != 'G')
            throw std::invalid_argument("Nucleotides are 'A', 'T', 'G' or 'C'.");
    }

}