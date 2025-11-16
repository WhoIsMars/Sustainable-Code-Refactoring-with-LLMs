#include <cmath>

constexpr double HOURS_PER_DAY = 8.0;
constexpr double WORKDAYS_PER_MONTH = 22.0;
constexpr double PERCENT_TO_DECIMAL = 0.01;

double daily_rate(double hourly_rate) {
    return hourly_rate * HOURS_PER_DAY;
}

double apply_discount(double before_discount, double discount) {
    return before_discount * (1.0 - discount * PERCENT_TO_DECIMAL);
}

int monthly_rate(double hourly_rate, double discount) {
    const double discounted_daily = hourly_rate * HOURS_PER_DAY * (1.0 - discount * PERCENT_TO_DECIMAL);
    return static_cast<int>(std::ceil(discounted_daily * WORKDAYS_PER_MONTH));
}

int days_in_budget(int budget, double hourly_rate, double discount) {
    const double discounted_daily = hourly_rate * HOURS_PER_DAY * (1.0 - discount * PERCENT_TO_DECIMAL);
    return static_cast<int>(budget / discounted_daily);
}