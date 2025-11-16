#include "hamming.h"
#include <stdexcept>
#include <string>

namespace hamming {
	int compute(const std::string& strand1, const std::string& strand2)
	{
		const std::size_t size = strand1.size();
		if (size != strand2.size()) {
			throw std::domain_error("Invalid Arguments");
		}
		
		int ans = 0;
		for (std::size_t i = 0; i < size; ++i) {
			ans += (strand1[i] != strand2[i]);
		}
		return ans;
	}
}