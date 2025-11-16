#include "nucleotide_count.h"
#include <array>

namespace nucleotide_count {

	counter::counter(const string& dnaStrand) : strand(dnaStrand), nucleotides{{{'A', 0}, {'C', 0}, {'G', 0}, {'T', 0}}} {
		for (char nucleotide : strand) {
			if (!is_valid(nucleotide))
				throw invalid_argument("Invalid nucleotide");
			++nucleotides[nucleotide];
		}
	}

	std::map<char, int> counter::nucleotide_counts() const {
		return nucleotides;
	}

	int counter::count(const char nucleotide) const {
		if (!is_valid(nucleotide))
			throw invalid_argument("Invalid nucleotide");
		return nucleotides.at(nucleotide);
	}

	bool counter::is_valid(char nucleotide) const {
		static const std::array<char, 4> valid_nucleotides = {'A', 'C', 'G', 'T'};
		for (char valid : valid_nucleotides) {
			if (nucleotide == valid) return true;
		}
		return false;
	}

}  // namespace nucleotide_count