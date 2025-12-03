#include "isogram.h"
#include <unordered_set>
#include <cctype>
#include <string>

namespace isogram {

	bool is_isogram(const std::string& word) {
	    std::unordered_set<char> seen;
	    for (char c : word) {
	        if (std::isalpha(c)) {
	            char lower_c = std::tolower(c);
	            if (!seen.insert(lower_c).second) {
	                return false;
	            }
	        }
	    }
	    return true;
	}

}