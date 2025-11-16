#pragma once
#include <vector>

namespace pascals_triangle {

[[nodiscard]]
constexpr auto factorial (const int &n) noexcept -> int { 
    return n == 0 ? 1 : n * factorial(n - 1);
}
[[nodiscard]]
constexpr auto binomial (const int &n, const int &k) noexcept -> int {
    return factorial(n) / (factorial(k) * factorial(n - k));
}
using ptriangle_t = std::vector<std::vector<int>>;
const auto generate_rows(const int&) noexcept -> ptriangle_t ;

} // namespace pascals_triangle 


#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif