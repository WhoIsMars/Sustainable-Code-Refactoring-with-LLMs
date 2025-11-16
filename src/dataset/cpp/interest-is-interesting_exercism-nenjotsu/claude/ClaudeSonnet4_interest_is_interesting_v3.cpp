// interest_rate returns the interest rate for the provided balance.
double interest_rate(double balance) {
    if (balance < 0) return 3.213;
    if (balance < 1000) return 0.5;
    if (balance < 5000) return 1.621;
    return 2.475;
}

// yearly_interest calculates the yearly interest for the provided balance.
double yearly_interest(double balance) {
    return balance * (interest_rate(balance) * 0.01);
}

// annual_balance_update calculates the annual balance update, taking into
// account the interest rate.
double annual_balance_update(double balance) {
    return balance * (1.0 + interest_rate(balance) * 0.01);
}

// years_until_desired_balance calculates the minimum number of years required
// to reach the desired balance.
int years_until_desired_balance(double balance, double target_balance) {
    if (balance >= target_balance) return 0;
    
    int years = 0;
    const double rate_multiplier = 1.0 + interest_rate(balance) * 0.01;
    
    while (balance < target_balance) {
        balance *= rate_multiplier;
        years++;
        
        if (((balance < 0) != (years == 1 ? balance / rate_multiplier < 0)) ||
            ((balance < 1000) != (years == 1 ? balance / rate_multiplier < 1000)) ||
            ((balance < 5000) != (years == 1 ? balance / rate_multiplier < 5000))) {
            const double new_rate_multiplier = 1.0 + interest_rate(balance) * 0.01;
            if (new_rate_multiplier != rate_multiplier) {
                while (balance < target_balance) {
                    balance *= 1.0 + interest_rate(balance) * 0.01;
                    years++;
                }
                break;
            }
        }
    }
    return years;
}