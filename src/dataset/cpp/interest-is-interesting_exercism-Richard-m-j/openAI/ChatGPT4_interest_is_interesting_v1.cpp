double interest_rate(double balance)
{
    if (balance < 0) return 3.213;
    if (balance < 1000) return 0.5;
    if (balance < 5000) return 1.621;
    return 2.475;
}

double yearly_interest(double balance)
{
    return (interest_rate(balance) * balance) / 100.0;
}

double annual_balance_update(double balance)
{
    return balance * (1.0 + interest_rate(balance) / 100.0);
}

int years_until_desired_balance(double balance, double target_balance)
{
    int years = 0;
    while (balance < target_balance)
    {
        balance *= (1.0 + interest_rate(balance) / 100.0);
        ++years;
    }
    return years;
}