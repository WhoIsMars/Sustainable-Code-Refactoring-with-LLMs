double interest_rate(double balance) {
    if (balance < 0) return 3.213;
    else if (balance < 1000) return 0.5;
    else if (balance < 5000) return 1.621;
    return 2.475;
}

double yearly_interest(double balance) {
    return (interest_rate(balance) * balance) * 0.01;
}

double annual_balance_update(double balance) {
    return balance + yearly_interest(balance);
}

int years_until_desired_balance(double balance, double target_balance) {
    int yrs = 0;
    while (balance < target_balance) {
        balance += (interest_rate(balance) * balance) * 0.01;
        ++yrs;
    }
    return yrs;
}