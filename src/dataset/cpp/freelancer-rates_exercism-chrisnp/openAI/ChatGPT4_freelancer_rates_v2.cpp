#include <cmath>

constexpr int work_hours_per_day = 8;
constexpr int work_days_per_month = 22;

// daily_rate calculates the daily rate given an hourly rate
[[nodiscard]]
constexpr double daily_rate(double hourly_rate) noexcept { 
    return hourly_rate * work_hours_per_day; 
}

// apply_discount calculates the price after a discount
[[nodiscard]]
constexpr double apply_discount(double before_discount, 
                                double discount) noexcept {
    return before_discount * (1.0 - discount / 100.0);
}

// monthly_rate calculates the monthly rate, given an hourly rate and a discount
// The returned monthly rate is rounded up to the nearest integer.
[[nodiscard]]
int monthly_rate(double hourly_rate, 
                 double discount) noexcept {
    return static_cast<int>(std::ceil(apply_discount(daily_rate(hourly_rate) * work_days_per_month, discount)));
}

// days_in_budget calculates the number of workdays given a budget, hourly rate, and discount. 
// The returned number of days is rounded down (take the floor) to the next integer.
[[nodiscard]]
int days_in_budget(int budget, 
                   double hourly_rate, 
                   double discount) noexcept {
    return static_cast<int>(budget / apply_discount(daily_rate(hourly_rate), discount));
}

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif