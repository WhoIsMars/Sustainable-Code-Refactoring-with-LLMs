#pragma once

#include "etl.h"
#include <map>
#include "test/catch.hpp"

using namespace std;

namespace etl {
	map<char, int> transform(map<int, vector<char>> oldData);
}  // namespace etl
