#include <cmath>

constexpr double HOURS_PER_DAY = 8.0;
constexpr double WORKING_DAYS_PER_MONTH = 22.0;
constexpr double PERCENT_TO_DECIMAL = 0.01;

inline double daily_rate(double hourly_rate) {
    return hourly_rate * HOURS_PER_DAY;
}

inline double apply_discount(double before_discount, double discount) {
    return before_discount * (1.0 - discount * PERCENT_TO_DECIMAL);
}

int monthly_rate(double hourly_rate, double discount) {
    const double total = hourly_rate * HOURS_PER_DAY * WORKING_DAYS_PER_MONTH;
    const double discounted_rate = total * (1.0 - discount * PERCENT_TO_DECIMAL);
    return static_cast<int>(std::ceil(discounted_rate));
}

int days_in_budget(int budget, double hourly_rate, double discount) {
    const double discounted_daily_rate = hourly_rate * HOURS_PER_DAY * (1.0 - discount * PERCENT_TO_DECIMAL);
    return static_cast<int>(budget / discounted_daily_rate);
}