double interest_rate(double balance) {
    return (balance < 0) ? 3.213 :
           (balance < 1000) ? 0.5 :
           (balance < 5000) ? 1.621 : 2.475;
}

double yearly_interest(double balance) {
    return balance * interest_rate(balance) * 0.01;
}

double annual_balance_update(double balance) {
    return balance + yearly_interest(balance);
}

int years_until_desired_balance(double balance, double target_balance) {
    int yrs = 0;
    while (balance < target_balance) {
        balance += balance * interest_rate(balance) * 0.01;
        ++yrs;
    }
    return yrs;
}