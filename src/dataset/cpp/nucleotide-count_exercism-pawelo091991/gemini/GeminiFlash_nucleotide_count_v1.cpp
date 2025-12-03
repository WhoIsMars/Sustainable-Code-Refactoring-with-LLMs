#include "nucleotide_count.h"
#include <algorithm>
#include <stdexcept>

namespace dna {
	counter::counter(const string& input) {
		data['A'] = 0;
		data['T'] = 0;
		data['C'] = 0;
		data['G'] = 0;

		for (char nucleotide : input) {
			switch (nucleotide) {
			case 'A':
			case 'T':
			case 'C':
			case 'G':
				data[nucleotide]++;
				break;
			default:
				throw std::invalid_argument("invalid nucleotide");
			}
		}
	}

	std::map<char, int> counter::nucleotide_counts() const {
		return data;
	}

	int counter::count(char nucleotide) const {
		if (data.find(nucleotide) == data.end()) {
			throw std::invalid_argument("invalid input argument");
		}
		return data.at(nucleotide);
	}
}