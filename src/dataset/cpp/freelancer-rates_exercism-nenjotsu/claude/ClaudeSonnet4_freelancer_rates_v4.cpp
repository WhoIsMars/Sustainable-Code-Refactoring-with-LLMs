#include <cmath>

double daily_rate(double hourly_rate) {
    return hourly_rate * 8.0;
}

double apply_discount(double before_discount, double discount) {
    return before_discount * (1.0 - discount * 0.01);
}

int monthly_rate(double hourly_rate, double discount) {
    const double daily = hourly_rate * 8.0;
    const double monthly = daily * 22.0;
    const double discounted = monthly * (1.0 - discount * 0.01);
    return static_cast<int>(std::ceil(discounted));
}

int days_in_budget(int budget, double hourly_rate, double discount) {
    const double daily = hourly_rate * 8.0;
    const double discounted_daily = daily * (1.0 - discount * 0.01);
    return static_cast<int>(budget / discounted_daily);
}