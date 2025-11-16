#include <cmath>

// daily_rate calculates the daily rate given an hourly rate
inline double daily_rate(double hourly_rate) {
    return hourly_rate * 8.0;
}

// apply_discount calculates the price after a discount
inline double apply_discount(double before_discount, double discount) {
    return before_discount * (1.0 - discount * 0.01);
}

// monthly_rate calculates the monthly rate, given an hourly rate and a discount
// The returned monthly rate is rounded up to the nearest integer.
inline int monthly_rate(double hourly_rate, double discount) {
    return static_cast<int>(std::ceil(apply_discount(daily_rate(hourly_rate) * 22.0, discount)));
}

// days_in_budget calculates the number of workdays given a budget, hourly rate,
// and discount The returned number of days is rounded down (take the floor) to
// the next integer.
inline int days_in_budget(int budget, double hourly_rate, double discount) {
    return static_cast<int>(budget / apply_discount(daily_rate(hourly_rate), discount));
}