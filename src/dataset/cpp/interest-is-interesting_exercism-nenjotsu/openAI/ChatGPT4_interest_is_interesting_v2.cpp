inline double interest_rate(double balance) {
    return (balance >= 5000) ? 2.475 :
           (balance >= 1000) ? 1.621 :
           (balance >= 0)    ? 0.5   : 3.213;
}

inline double yearly_interest(double balance) {
    return balance * (interest_rate(balance) / 100);
}

inline double annual_balance_update(double balance) {
    return balance + yearly_interest(balance);
}

int years_until_desired_balance(double balance, double target_balance) {
    int years = 0;
    while (balance < target_balance) {
        balance += balance * (interest_rate(balance) / 100);
        years++;
    }
    return years;
}