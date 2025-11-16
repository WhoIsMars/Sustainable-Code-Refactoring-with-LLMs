#include <cmath>

inline double daily_rate(double hourly_rate)
{
    return hourly_rate * 8;
}

inline double apply_discount(double before_discount, double discount)
{
    return before_discount * (1 - discount / 100);
}

int monthly_rate(double hourly_rate, double discount)
{
    return static_cast<int>(std::ceil(apply_discount(176 * hourly_rate, discount)));
}

int days_in_budget(int budget, double hourly_rate, double discount)
{
    return static_cast<int>(budget * 22 / std::ceil(apply_discount(176 * hourly_rate, discount)));
}