#include "etl.h"
#include <map>

namespace etl {	
	map<char, int> transform(map<int, vector<char>> oldData) {
		map<char, int> newData;
		for (auto const& data : oldData) {
			int points = data.first;
			vector<char> letters = data.second;
			for (char letter : letters) {
				newData[tolower(letter)] = points;
			}
		}
		return newData;
	}
}  // namespace etl
