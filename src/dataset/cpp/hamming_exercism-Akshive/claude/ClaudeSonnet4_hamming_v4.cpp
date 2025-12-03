#include "hamming.h"
#include <stdexcept>
#include <string>

namespace hamming {
	int compute(const std::string& stand1, const std::string& strand2)
	{
		const std::size_t size = strand2.size();
		if(size != stand1.size()) {
			throw std::domain_error("Invalid Arguments");
		}
		
		int ans = 0;
		for(std::size_t i = 0; i < size; ++i) {
			ans += (stand1[i] != strand2[i]);
		}
		return ans;
	}
}