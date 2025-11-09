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

double yearly_interest(double balance) {
    return balance * (interest_rate(balance) * 0.01);
}

double annual_balance_update(double balance) {
    return balance * (1.0 + interest_rate(balance) * 0.01);
}

int years_until_desired_balance(double balance, double target_balance) {
    if (balance >= target_balance) {
        return 0;
    }
    
    int years = 0;
    while (balance < target_balance) {
        const double rate = interest_rate(balance);
        balance *= (1.0 + rate * 0.01);
        ++years;
    }
    return years;
}