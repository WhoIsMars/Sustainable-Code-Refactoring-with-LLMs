// interest_rate returns the interest rate for the provided balance.
[[nodiscard]]
auto interest_rate(const double &balance) noexcept -> double {
    return balance < 0 
           ? 3.213 : 
           balance < 1000 
           ? 0.500 : 
           balance < 5000 
           ? 1.621 
           : 2.475 ;
}

// yearly_interest calculates the yearly interest for the provided balance.
[[nodiscard]]
auto yearly_interest(const double &balance) noexcept -> double {
    return balance * interest_rate(balance) / 100 ;
}

// annual_balance_update calculates the annual balance update, taking into
// account the interest rate.
auto annual_balance_update(const double &balance) noexcept -> double {
    return balance + yearly_interest(balance);
}

// years_until_desired_balance calculates the minimum number of years required
// to reach the desired balance.
auto years_until_desired_balance(double &balance, 
                                 const double &target_balance) noexcept -> int {
    int years { 0 };
    while (balance < target_balance) {
        balance += yearly_interest(balance);
        ++years;
    }
    return years;
}



#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif