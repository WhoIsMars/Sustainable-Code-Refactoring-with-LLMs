inline double interest_rate(double balance) {
    return (balance < 0) ? 3.213 :
           (balance < 1000) ? 0.5 :
           (balance < 5000) ? 1.621 : 2.475;
}

inline double yearly_interest(double balance) {
    return (interest_rate(balance) / 100) * balance;
}

inline double annual_balance_update(double balance) {
    return balance + yearly_interest(balance);
}

int years_until_desired_balance(double balance, double target_balance) {
    int years = 0;
    while (balance < target_balance) {
        balance += (interest_rate(balance) / 100) * balance;
        ++years;
    }
    return years;
}