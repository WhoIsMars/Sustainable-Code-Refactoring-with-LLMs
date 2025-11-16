#pragma once

#include <vector>
#include <string>

namespace lasagna_master {

using namespace std;

struct amount {
    int noodles;
    double sauce;
};

auto preparationTime(const vector<string>&, int time = 2) -> int;

auto quantities(const vector<string>&) -> amount;

auto addSecretIngredient(vector<string>&, const vector<string>&) -> void;

auto addSecretIngredient(vector<string>&, const string&) -> void;

auto scaleRecipe(const vector<double>&, int) -> vector<double>;

}  // namespace lasagna_master



#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif