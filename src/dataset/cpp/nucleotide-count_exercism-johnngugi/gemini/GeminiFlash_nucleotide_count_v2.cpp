#include "nucleotide_count.h"
#include <stdexcept>
#include <algorithm>

using namespace dna;
using namespace std;

counter::counter(const string& a) : strand(a) {
    nucleotide_count['A'] = 0;
    nucleotide_count['C'] = 0;
    nucleotide_count['G'] = 0;
    nucleotide_count['T'] = 0;

    for (char c : a) {
        if (c == 'A' || c == 'C' || c == 'G' || c == 'T') {
            ++nucleotide_count[c];
        } else {
            throw invalid_argument("Invalid nucleotide: " + string(1, c));
        }
    }
}

int counter::count(char nucleotide) const {
    if (nucleotide == 'A' || nucleotide == 'C' || nucleotide == 'G' || nucleotide == 'T') {
        return nucleotide_count.at(nucleotide);
    } else {
        throw invalid_argument("Invalid nucleotide: " + string(1, nucleotide));
    }
}

map<char, int> counter::nucleotide_counts() const {
    return nucleotide_count;
}