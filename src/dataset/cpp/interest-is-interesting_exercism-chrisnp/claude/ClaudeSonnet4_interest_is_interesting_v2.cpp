// interest_rate returns the interest rate for the provided balance.
[[nodiscard]]
auto interest_rate(double balance) noexcept -> double {
    if (balance < 0) return 3.213;
    if (balance < 1000) return 0.500;
    if (balance < 5000) return 1.621;
    return 2.475;
}

// yearly_interest calculates the yearly interest for the provided balance.
[[nodiscard]]
auto yearly_interest(double balance) noexcept -> double {
    return balance * interest_rate(balance) * 0.01;
}

// annual_balance_update calculates the annual balance update, taking into
// account the interest rate.
auto annual_balance_update(double balance) noexcept -> double {
    return balance * (1.0 + interest_rate(balance) * 0.01);
}

// years_until_desired_balance calculates the minimum number of years required
// to reach the desired balance.
auto years_until_desired_balance(double &balance, 
                                 double target_balance) noexcept -> int {
    int years = 0;
    while (balance < target_balance) {
        balance *= (1.0 + interest_rate(balance) * 0.01);
        ++years;
    }
    return years;
}

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif