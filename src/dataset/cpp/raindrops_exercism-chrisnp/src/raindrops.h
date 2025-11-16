#pragma once

#include <string>
#include <vector>

namespace raindrops {

using namespace std;

static const vector<pair<int, string>> drops {
  {3, "Pling"}, {5, "Plang"}, {7, "Plong"}
};

string convert(int n);

}  // namespace raindrops

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif