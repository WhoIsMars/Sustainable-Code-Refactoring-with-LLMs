#include "nucleotide_count.h"
#include <array>

namespace dna {
	counter::counter(const std::string& input) : data{{{'A', 0}, {'T', 0}, {'C', 0}, {'G', 0}}} {
		for (char nucleotide : input) {
			if (data.count(nucleotide))
				data[nucleotide]++;
			else
				throw std::invalid_argument("invalid nucleotide");
		}
	}

	std::map<char, int> counter::nucleotide_counts() const {
		return data;
	}

	int counter::count(char input) const {
		if (data.count(input))
			return data.at(input);
		else
			throw std::invalid_argument("invalid input argument");
	}
}