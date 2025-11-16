#include <cmath>

constexpr int work_hours_per_day = 8;
constexpr int work_days_per_month = 22;

[[nodiscard]]
constexpr auto daily_rate(const double hourly_rate) noexcept -> double { 
    return hourly_rate * work_hours_per_day; 
}

[[nodiscard]]
constexpr auto apply_discount(const double before_discount, 
                              const double discount) noexcept -> double {
    return before_discount * (1.0 - discount / 100.0);
}

auto monthly_rate(const double hourly_rate, 
                  const double discount) noexcept -> int {
    const double full_monthly_rate = daily_rate(hourly_rate) * work_days_per_month;
    return static_cast<int>(std::ceil(apply_discount(full_monthly_rate, discount)));
}

auto days_in_budget(const int budget, 
                    const double hourly_rate, 
                    const double discount) noexcept -> int {
    const double discounted_daily_rate = apply_discount(daily_rate(hourly_rate), discount);
    return static_cast<int>(budget / discounted_daily_rate);
}

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif