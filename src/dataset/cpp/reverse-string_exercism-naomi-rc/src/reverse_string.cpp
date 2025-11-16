#include "reverse_string.h"
#include <string>

using namespace std;

namespace reverse_string {
	string reverse_string(string word) {
		return string(word.rbegin(), word.rend());
	}
}  // namespace reverse_string
