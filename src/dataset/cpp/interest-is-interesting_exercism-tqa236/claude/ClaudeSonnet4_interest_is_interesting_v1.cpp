// interest_rate returns the interest rate for the provided balance.
double interest_rate(double balance)
{
    if (balance < 0) return 3.213;
    if (balance < 1000) return 0.5;
    if (balance < 5000) return 1.621;
    return 2.475;
}

// yearly_interest calculates the yearly interest for the provided balance.
double yearly_interest(double balance)
{
    if (balance < 0) return balance * 0.03213;
    if (balance < 1000) return balance * 0.005;
    if (balance < 5000) return balance * 0.01621;
    return balance * 0.02475;
}

// annual_balance_update calculates the annual balance update, taking into
// account the interest rate.
double annual_balance_update(double balance)
{
    if (balance < 0) return balance * 1.03213;
    if (balance < 1000) return balance * 1.005;
    if (balance < 5000) return balance * 1.01621;
    return balance * 1.02475;
}

// years_until_desired_balance calculates the minimum number of years required
// to reach the desired balance.
int years_until_desired_balance(double balance, double target_balance)
{
    if (balance >= target_balance) return 0;
    
    int required_years = 0;
    while (balance < target_balance)
    {
        if (balance < 0) balance *= 1.03213;
        else if (balance < 1000) balance *= 1.005;
        else if (balance < 5000) balance *= 1.01621;
        else balance *= 1.02475;
        required_years++;
    }
    
    return required_years;
}