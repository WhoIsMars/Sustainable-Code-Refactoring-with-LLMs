#include "reverse_string.h"
#include <string>
#include <algorithm>

using namespace std;

namespace reverse_string {
	string reverse_string(string word) {
		reverse(word.begin(), word.end());
		return word;
	}
}  // namespace reverse_string