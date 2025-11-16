#pragma once
#include <string>

namespace vehicle_purchase {
    using string = std::string;
 
    template<typename T>
    constexpr auto min (T &x, T &y) noexcept -> bool { return x < y ? x : y; };
    
    auto needs_license(const string&) noexcept -> bool;
    auto choose_vehicle(const string&, const string&) noexcept -> string;
    auto calculate_resell_price(const double&, const double&) noexcept -> double;

}  // namespace vehicle_purchase


#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif