#include "nucleotide_count.h"

namespace nucleotide_count {

	counter::counter(string dnaStrand) : strand(std::move(dnaStrand)) {
		nucleotides['A'] = 0;
		nucleotides['C'] = 0;
		nucleotides['G'] = 0;
		nucleotides['T'] = 0;
		
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
		auto it = nucleotides.find(nucleotide);
		return (it != nucleotides.end()) ? it->second : 0;
	}

	bool counter::is_valid(char nucleotide) const {		
		return nucleotide == 'A' || nucleotide == 'C' || nucleotide == 'G' || nucleotide == 'T';
	}

}  // namespace nucleotide_count