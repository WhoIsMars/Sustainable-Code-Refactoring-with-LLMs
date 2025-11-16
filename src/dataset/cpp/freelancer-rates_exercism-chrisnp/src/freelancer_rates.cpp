#include <cmath>

constexpr auto work_hours_per_day { 8 };
constexpr auto work_days_per_month { 22 };

// daily_rate calculates the daily rate given an hourly rate
[[nodiscard]]
auto daily_rate(const double &hourly_rate) noexcept -> double { 
    return hourly_rate * work_hours_per_day; 
}

// apply_discount calculates the price after a discount
[[nodiscard]]
auto apply_discount(const double &before_discount, 
                    const double &discount) noexcept -> double {
    return before_discount * (100 - discount) / 100.0;
}

// monthly_rate calculates the monthly rate, given an hourly rate and a discount
// The returned monthly rate is rounded up to the nearest integer.
auto monthly_rate(const double &hourly_rate, 
                  const double &discount) noexcept -> int {
    double full_monthly_rate = daily_rate(hourly_rate) * work_days_per_month;
    return std::ceil(apply_discount(full_monthly_rate, discount));
}

// days_in_budget calculates the number of workdays given a budget, hourly rate, and discount. 
// The returned number of days is rounded down (take the floor) to the next integer.
auto days_in_budget(const int &budget, 
                    const double &hourly_rate, 
                    const double &discount) noexcept -> int {
    double full_daily_rate = daily_rate(hourly_rate);
    double discounted_daily_rate = apply_discount(full_daily_rate, discount);
    return std::floor(budget / discounted_daily_rate);
}



#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif