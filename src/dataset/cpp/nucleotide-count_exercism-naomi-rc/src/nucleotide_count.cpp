#include "nucleotide_count.h"

namespace nucleotide_count {

	counter::counter(string dnaStrand) : strand(dnaStrand) {
		for (char nucleotide : strand) {
			if (!is_valid(nucleotide))
				throw invalid_argument("Invalid nucleotide");
			nucleotides[nucleotide]++;
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
		return valid_nucleotides.find(nucleotide) != std::string::npos;
	}

	
}  // namespace nucleotide_count
