#include <cmath>

constexpr int work_hours_per_day = 8;
constexpr int work_days_per_month = 22;

// daily_rate calculates the daily rate given an hourly rate
[[nodiscard]]
constexpr auto daily_rate(const double hourly_rate) noexcept -> double { 
    return hourly_rate * work_hours_per_day; 
}

// apply_discount calculates the price after a discount
[[nodiscard]]
constexpr auto apply_discount(const double before_discount, 
                              const double discount) noexcept -> double {
    return before_discount * (1.0 - discount / 100.0);
}

// monthly_rate calculates the monthly rate, given an hourly rate and a discount
// The returned monthly rate is rounded up to the nearest integer.
[[nodiscard]]
auto monthly_rate(const double hourly_rate, 
                  const double discount) noexcept -> int {
    return static_cast<int>(std::ceil(apply_discount(daily_rate(hourly_rate) * work_days_per_month, discount)));
}

// days_in_budget calculates the number of workdays given a budget, hourly rate, and discount. 
// The returned number of days is rounded down (take the floor) to the next integer.
[[nodiscard]]
auto days_in_budget(const int budget, 
                    const double hourly_rate, 
                    const double discount) noexcept -> int {
    return static_cast<int>(budget / apply_discount(daily_rate(hourly_rate), discount));
}

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif