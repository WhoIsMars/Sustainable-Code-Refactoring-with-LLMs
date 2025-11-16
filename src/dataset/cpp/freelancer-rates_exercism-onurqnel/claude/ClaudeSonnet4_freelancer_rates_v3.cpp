#include <cmath>

double daily_rate(double hourly_rate)
{
    return hourly_rate * 8.0;
}

double apply_discount(double before_discount, double discount)
{
    return before_discount * (1.0 - discount * 0.01);
}

int monthly_rate(double hourly_rate, double discount)
{
    const double monthly_base = hourly_rate * 176.0; // 22 * 8
    const double discounted = monthly_base * (1.0 - discount * 0.01);
    return static_cast<int>(std::ceil(discounted));
}

int days_in_budget(int budget, double hourly_rate, double discount)
{
    const double monthly_base = hourly_rate * 176.0; // 22 * 8
    const double discounted_monthly = monthly_base * (1.0 - discount * 0.01);
    const double monthly_rounded = std::ceil(discounted_monthly);
    const double daily_cost = monthly_rounded / 22.0;
    return static_cast<int>(budget / daily_cost);
}