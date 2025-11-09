#include <cmath>

double daily_rate(double hourly_rate) {
    return hourly_rate * 8.0;
}

double apply_discount(double before_discount, double discount) {
    return before_discount * (1.0 - discount * 0.01);
}

int monthly_rate(double hourly_rate, double discount) {
    const double total = hourly_rate * 176.0;
    const double discounted_rate = total * (1.0 - discount * 0.01);
    return static_cast<int>(std::ceil(discounted_rate));
}

int days_in_budget(int budget, double hourly_rate, double discount) {
    const double discounted_daily_rate = hourly_rate * 8.0 * (1.0 - discount * 0.01);
    return static_cast<int>(budget / discounted_daily_rate);
}