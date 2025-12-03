// interest_rate returns the interest rate for the provided balance.
double interest_rate(double balance) {
    if (balance < 0) {
        return 3.213;
    }
    if (balance < 1000) {
        return 0.5;
    }
    if (balance < 5000) {
        return 1.621;
    }
    return 2.475;
}

// yearly_interest calculates the yearly interest for the provided balance.
double yearly_interest(double balance) {
    double rate = interest_rate(balance);
    return (rate / 100.0) * balance;
}

// annual_balance_update calculates the annual balance update, taking into
// account the interest rate.
double annual_balance_update(double balance) {
    return balance * (1.0 + (interest_rate(balance) / 100.0));
}

// years_until_desired_balance calculates the minimum number of years required
// to reach the desired balance.
int years_until_desired_balance(double balance, double target_balance) {
    if (balance >= target_balance) {
        return 0;
    }

    int years = 0;
    double rate;
    while (balance < target_balance) {
        rate = interest_rate(balance);
        balance *= (1.0 + (rate / 100.0));
        years++;

        if (years > 1000) return years; // Add a failsafe to prevent infinite loops
    }
    return years;
}