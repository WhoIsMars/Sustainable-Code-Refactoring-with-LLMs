#include "nucleotide_count.h"
#include <array>

namespace nucleotide_count {

	counter::counter(string dnaStrand) : strand(std::move(dnaStrand)), nucleotides{{{'A', 0}, {'C', 0}, {'G', 0}, {'T', 0}}} {
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
		return std::find(valid_nucleotides.begin(), valid_nucleotides.end(), nucleotide) != valid_nucleotides.end();
	}

}  // namespace nucleotide_count