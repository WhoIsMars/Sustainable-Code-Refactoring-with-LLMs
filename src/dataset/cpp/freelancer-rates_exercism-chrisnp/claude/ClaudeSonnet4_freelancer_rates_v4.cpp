#include <cmath>

constexpr auto work_hours_per_day { 8 };
constexpr auto work_days_per_month { 22 };

[[nodiscard]]
auto daily_rate(double hourly_rate) noexcept -> double { 
    return hourly_rate * work_hours_per_day; 
}

[[nodiscard]]
auto apply_discount(double before_discount, double discount) noexcept -> double {
    return before_discount * (1.0 - discount * 0.01);
}

auto monthly_rate(double hourly_rate, double discount) noexcept -> int {
    const double full_monthly_rate = hourly_rate * work_hours_per_day * work_days_per_month;
    const double discounted_rate = full_monthly_rate * (1.0 - discount * 0.01);
    return static_cast<int>(std::ceil(discounted_rate));
}

auto days_in_budget(int budget, double hourly_rate, double discount) noexcept -> int {
    const double discounted_daily_rate = hourly_rate * work_hours_per_day * (1.0 - discount * 0.01);
    return static_cast<int>(budget / discounted_daily_rate);
}

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif