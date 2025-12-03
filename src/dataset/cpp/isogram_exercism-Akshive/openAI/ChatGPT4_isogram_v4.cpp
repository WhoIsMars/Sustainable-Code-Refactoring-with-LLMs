#include "isogram.h"
#include <unordered_set>
#include <cctype>
#include <string>

namespace isogram {

	bool is_isogram(const std::string& word) {
	    std::unordered_set<char> seen;
	    for (char c : word) {
	        c = std::tolower(c);
	        if (std::isalpha(c)) {
	            if (!seen.insert(c).second) {
	                return false;
	            }
	        }
	    }
	    return true;
	}

}