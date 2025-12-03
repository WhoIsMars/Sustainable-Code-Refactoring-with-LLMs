#include "isogram.h"
#include <cctype>
using namespace std;

namespace isogram {

	bool is_isogram(string word) {
		bool seen[26] = {false};
		for (char c : word) {
			if (isalpha(c)) {
				int index = tolower(c) - 'a';
				if (seen[index]) return false;
				seen[index] = true;
			}
		}
		return true;
	}

}