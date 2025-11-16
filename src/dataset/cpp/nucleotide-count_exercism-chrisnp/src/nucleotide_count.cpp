#include "nucleotide_count.h"
#include <stdexcept>

nucleotide_count::counts_t nucleotide_count::count(std::string strand) {
    nucleotide_count::counts_t counts = {
        {'A', 0}, {'C', 0}, {'G', 0}, {'T', 0}
    };
    for (auto n : strand) {
        switch(n) {
            case 'A':
            case 'C':
            case 'G':
            case 'T':
                ++counts[n];
                break;
            default: 
                throw std::invalid_argument("invalid nucleotide");
            }
        }
    return counts;
}