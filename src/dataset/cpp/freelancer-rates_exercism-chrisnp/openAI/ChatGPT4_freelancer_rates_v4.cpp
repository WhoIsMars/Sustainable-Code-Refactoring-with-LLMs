#include <cmath>

constexpr double work_hours_per_day = 8.0;
constexpr double work_days_per_month = 22.0;

[[nodiscard]]
constexpr auto daily_rate(const double hourly_rate) noexcept -> double { 
    return hourly_rate * work_hours_per_day; 
}

[[nodiscard]]
constexpr auto apply_discount(const double before_discount, 
                              const double discount) noexcept -> double {
    return before_discount * (1.0 - discount / 100.0);
}

constexpr auto monthly_rate(const double hourly_rate, 
                            const double discount) noexcept -> int {
    return static_cast<int>(std::ceil(apply_discount(daily_rate(hourly_rate) * work_days_per_month, discount)));
}

constexpr auto days_in_budget(const int budget, 
                              const double hourly_rate, 
                              const double discount) noexcept -> int {
    return static_cast<int>(budget / apply_discount(daily_rate(hourly_rate), discount));
}

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif