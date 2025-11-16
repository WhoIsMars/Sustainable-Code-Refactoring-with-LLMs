#include "bank_account.h"

#include <stdexcept>
#include <limits>

namespace Bankaccount {

Bankaccount::Bankaccount() : _isopen(false), _balance(0) {}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(_mtx);

    if (_isopen) {
        throw std::runtime_error("Account already opened.");
    }
    _isopen = true;
    _balance = 0;
}

void Bankaccount::deposit(balance_t amount) {
    std::lock_guard<std::mutex> lock(_mtx);

    if (!_isopen) {
        throw std::runtime_error("Account not opened.");
    }

    if (amount < 0) {
        throw std::runtime_error("Cannot deposit negative amount.");
    }

    if (std::numeric_limits<balance_t>::max() - _balance < amount) {
        throw std::runtime_error("Deposit amount exceeds maximum balance.");
    }

    _balance += amount;
}

void Bankaccount::withdraw(balance_t amount) {
    std::lock_guard<std::mutex> lock(_mtx);

    if (!_isopen) {
        throw std::runtime_error("Account not opened.");
    }

    if (amount < 0) {
        throw std::runtime_error("Cannot withdraw negative amount.");
    }

    if (amount > _balance) {
        throw std::runtime_error("Withdrawal amount exceeds current balance.");
    }

    _balance -= amount;
}

balance_t Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(_mtx);

    if (!_isopen) {
        throw std::runtime_error("Account not opened.");
    }
    return _balance;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(_mtx);
    if (!_isopen) {
        throw std::runtime_error("Account not opened.");
    }
    _isopen = false;
    _balance = 0;
}

}