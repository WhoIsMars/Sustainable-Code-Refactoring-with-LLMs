#include <cmath>

constexpr double HOURS_PER_DAY = 8.0;
constexpr double DAYS_PER_MONTH = 22.0;
constexpr double PERCENT_DIVISOR = 100.0;

inline double daily_rate(double hourly_rate) noexcept
{
    return hourly_rate * HOURS_PER_DAY;
}

inline double apply_discount(double before_discount, double discount) noexcept
{
    return before_discount * (PERCENT_DIVISOR - discount) / PERCENT_DIVISOR;
}

int monthly_rate(double hourly_rate, double discount) noexcept
{
    const double monthly_before_discount = hourly_rate * HOURS_PER_DAY * DAYS_PER_MONTH;
    const double monthly_after_discount = monthly_before_discount * (PERCENT_DIVISOR - discount) / PERCENT_DIVISOR;
    return static_cast<int>(std::ceil(monthly_after_discount));
}

int days_in_budget(int budget, double hourly_rate, double discount) noexcept
{
    const double daily_cost = hourly_rate * HOURS_PER_DAY * (PERCENT_DIVISOR - discount) / PERCENT_DIVISOR;
    return static_cast<int>(budget / daily_cost);
}