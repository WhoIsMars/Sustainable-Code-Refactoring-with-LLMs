#include <cmath>

// interest_rate returns the interest rate for the provided balance.
double interest_rate(double balance) {
    if (balance < 0) {
        return 3.213; // Negative balance
    }
    if (balance < 1000) {
        return 0.5;   // Balance less than 1000
    }
    if (balance < 5000) {
        return 1.621; // Balance between 1000 and 5000
    }
    return 2.475; // Balance of 5000 or more
}

// yearly_interest calculates the yearly interest for the provided balance.
double yearly_interest(double balance) {
    double rate = interest_rate(balance);
    return balance * (rate * 0.01);
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

    double rate;
    if (balance < 0) {
        rate = 3.213 * 0.01;
    } else if (balance < 1000) {
        rate = 0.5 * 0.01;
    } else if (balance < 5000) {
        rate = 1.621 * 0.01;
    } else {
        rate = 2.475 * 0.01;
    }

    if (rate <= 0) {
        return -1;
    }

    int years = 0;
    if (rate > 0) {
        years = static_cast<int>(std::ceil(std::log(target_balance / balance) / std::log(1 + rate)));
    }

    if (years < 0) {
        years = 1000;
        while (balance < target_balance && years > 0) {
            balance = annual_balance_update(balance);
            years--;
        }
        if (years == 0 && balance < target_balance) return -1;
        return 1000 - years;
    }

    return years;
}