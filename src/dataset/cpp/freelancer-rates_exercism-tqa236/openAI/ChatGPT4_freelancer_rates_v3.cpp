#include <cmath>

inline double daily_rate(double hourly_rate) {
    return hourly_rate * 8;
}

inline double apply_discount(double before_discount, double discount) {
    return before_discount * (1.0 - discount / 100.0);
}

inline int monthly_rate(double hourly_rate, double discount) {
    return static_cast<int>(std::ceil(apply_discount(daily_rate(hourly_rate) * 22, discount)));
}

inline int days_in_budget(int budget, double hourly_rate, double discount) {
    return static_cast<int>(budget / apply_discount(daily_rate(hourly_rate), discount));
}