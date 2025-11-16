#pragma once

#include <vector>

namespace triangle {
    
enum class flavor {
    equilateral, 
    isosceles,
    scalene
};

auto kind(double, double, double) -> flavor;

}  // namespace triangle

namespace doubles {

[[nodiscard, gnu::const]] 
auto maximum(std::vector<double>&) noexcept -> double;

[[nodiscard, gnu::const]]    
auto minimum(std::vector<double>&) noexcept -> double;

[[nodiscard, gnu::const]]    
auto kahanSum(std::vector<double>&) noexcept -> double; 

} // namespace doubles

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif