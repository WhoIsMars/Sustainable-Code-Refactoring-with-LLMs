#include <cmath>

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
    return balance * interest_rate(balance) / 100.0;
}

// annual_balance_update calculates the annual balance update, taking into
// account the interest rate.
double annual_balance_update(double balance) {
    return balance + yearly_interest(balance);
}

// years_until_desired_balance calculates the minimum number of years required
// to reach the desired balance.
int years_until_desired_balance(double balance, double target_balance) {
    if (balance >= target_balance) {
        return 0;
    }

    double rate = 0.0;
    if (balance < 0) {
        rate = 3.213 / 100.0;
    } else if (balance < 1000) {
        rate = 0.5 / 100.0;
    } else if (balance < 5000) {
        rate = 1.621 / 100.0;
    } else {
        rate = 2.475 / 100.0;
    }

    if (rate <= 0.0) {
        return -1; 
    }

    int years = 0;
    if (rate > 0.0) {
        years = static_cast<int>(ceil(log(target_balance / balance) / log(1 + rate)));
    }
    
    if (years < 0) return -1;

    double updated_balance = balance;
    for (int i = 0; i < years; ++i) {
        updated_balance = annual_balance_update(updated_balance);
    }

    if (updated_balance < target_balance) {
        years++;
    }

    return years;
}