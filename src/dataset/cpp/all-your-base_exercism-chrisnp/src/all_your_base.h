#pragma once

#include <vector>

namespace all_your_base {

using uint = unsigned int;
typedef std::vector<uint> digits_t;
auto convert(uint, const digits_t&, uint) -> digits_t;

}  // namespace all_your_base

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif