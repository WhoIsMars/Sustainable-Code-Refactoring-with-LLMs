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
    const double monthly_before_discount = hourly_rate * 176.0;
    const double monthly_after_discount = monthly_before_discount * (1.0 - discount * 0.01);
    return static_cast<int>(std::ceil(monthly_after_discount));
}

int days_in_budget(int budget, double hourly_rate, double discount)
{
    const double daily_cost = hourly_rate * 8.0 * (1.0 - discount * 0.01);
    return static_cast<int>(budget / daily_cost);
}