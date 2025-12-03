#include "nucleotide_count.h"
#include <unordered_map>

namespace dna {
	counter::counter(const std::string& input) : data{{'A', 0}, {'T', 0}, {'C', 0}, {'G', 0}} {
		for (char nucleotide : input) {
			if (data.find(nucleotide) != data.end()) {
				data[nucleotide]++;
			} else {
				throw std::invalid_argument("invalid nucleotide");
			}
		}
	}

	std::unordered_map<char, int> counter::nucleotide_counts() const {
		return data;
	}

	int counter::count(char input) const {
		auto it = data.find(input);
		if (it != data.end()) {
			return it->second;
		} else {
			throw std::invalid_argument("invalid input argument");
		}
	}
}