#include "nucleotide_count.h"

namespace nucleotide_count {

	counter::counter(const string& dnaStrand) : strand(dnaStrand) {
		nucleotides['A'] = 0;
		nucleotides['C'] = 0;
		nucleotides['G'] = 0;
		nucleotides['T'] = 0;
		
		for (char nucleotide : strand) {
			switch (nucleotide) {
				case 'A':
				case 'C':
				case 'G':
				case 'T':
					nucleotides[nucleotide]++;
					break;
				default:
					throw invalid_argument("Invalid nucleotide");
			}
		}
	}

	const std::map<char, int>& counter::nucleotide_counts() const {
		return nucleotides;
	}

	int counter::count(const char nucleotide) const {
		switch (nucleotide) {
			case 'A':
			case 'C':
			case 'G':
			case 'T':
				return nucleotides.at(nucleotide);
			default:
				throw invalid_argument("Invalid nucleotide");
		}
	}

	bool counter::is_valid(char nucleotide) const {		
		return nucleotide == 'A' || nucleotide == 'C' || nucleotide == 'G' || nucleotide == 'T';
	}

}  // namespace nucleotide_count