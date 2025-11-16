#pragma once

#include <vector>

namespace nth_prime {

auto nth(const unsigned long &) -> unsigned long;
[[gnu::const]] auto is_prime(const int &) noexcept -> bool;

}  // namespace nth_prime

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif