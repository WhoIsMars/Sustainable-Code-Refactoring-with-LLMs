#include <cmath>

constexpr auto work_hours_per_day { 8 };
constexpr auto work_days_per_month { 22 };
constexpr auto work_hours_per_month { work_hours_per_day * work_days_per_month };
constexpr auto percent_divisor { 100.0 };

[[nodiscard]]
constexpr auto daily_rate(const double hourly_rate) noexcept -> double { 
    return hourly_rate * work_hours_per_day; 
}

[[nodiscard]]
constexpr auto apply_discount(const double before_discount, 
                             const double discount) noexcept -> double {
    return before_discount * (percent_divisor - discount) / percent_divisor;
}

auto monthly_rate(const double hourly_rate, 
                  const double discount) noexcept -> int {
    const double full_monthly_rate = hourly_rate * work_hours_per_month;
    return static_cast<int>(std::ceil(apply_discount(full_monthly_rate, discount)));
}

auto days_in_budget(const int budget, 
                    const double hourly_rate, 
                    const double discount) noexcept -> int {
    const double discounted_daily_rate = apply_discount(hourly_rate * work_hours_per_day, discount);
    return static_cast<int>(budget / discounted_daily_rate);
}

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif