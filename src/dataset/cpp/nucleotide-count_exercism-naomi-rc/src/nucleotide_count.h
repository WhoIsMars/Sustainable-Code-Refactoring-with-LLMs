#pragma once
#include <string>
#include <map>
#include <stdexcept>

using namespace std;

namespace nucleotide_count {
	class counter {
		public:
			
			counter(string dnaStrand);

			std::map<char, int> nucleotide_counts() const;		

			int count(const char nucleotide) const;

			bool is_valid(char nucleotide) const;
			
		private:

			const string strand;

			const string valid_nucleotides = "ATCG";

			map<char, int> nucleotides{ {'A', 0}, {'T', 0}, {'C', 0}, {'G', 0} };
	};
}  // namespace nucleotide_count
