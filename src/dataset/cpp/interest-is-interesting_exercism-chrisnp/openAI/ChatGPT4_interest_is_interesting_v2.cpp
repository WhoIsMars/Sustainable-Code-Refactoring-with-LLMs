[[nodiscard]]
constexpr auto interest_rate(const double balance) noexcept -> double {
    if (balance < 0) return 3.213;
    if (balance < 1000) return 0.500;
    if (balance < 5000) return 1.621;
    return 2.475;
}

[[nodiscard]]
constexpr auto yearly_interest(const double balance) noexcept -> double {
    return balance * interest_rate(balance) / 100.0;
}

constexpr auto annual_balance_update(const double balance) noexcept -> double {
    return balance + yearly_interest(balance);
}

constexpr auto years_until_desired_balance(double balance, 
                                           const double target_balance) noexcept -> int {
    int years = 0;
    while (balance < target_balance) {
        balance += yearly_interest(balance);
        ++years;
    }
    return years;
}

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif