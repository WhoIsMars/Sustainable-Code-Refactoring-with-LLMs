#include "nucleotide_count.h"

namespace dna {
    counter::counter(string input) {
        data['A'] = 0;
        data['T'] = 0;
        data['C'] = 0;
        data['G'] = 0;

        for (char c : input) {
            switch (c) {
                case 'A':
                case 'T':
                case 'C':
                case 'G':
                    data[c]++;
                    break;
                default:
                    throw std::invalid_argument("invalid nucleotide");
            }
        }
    }

    std::map<char, int> counter::nucleotide_counts() const {
        return data;
    }

    int counter::count(char input) const {
        switch (input) {
            case 'A':
            case 'T':
            case 'C':
            case 'G':
                return data.at(input);
            default:
                throw std::invalid_argument("invalid input argument");
        }
    }
}