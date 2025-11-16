#include "bank_account.h"

#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : _isopen(false), _balance(0) {}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(_mtx);

    if (_isopen) {
        throw std::runtime_error("Account not opened.");
    }
    _isopen = true;
    _balance = 0;
}

void Bankaccount::deposit(balance_t amount) {
    if (amount < 0) {
        throw std::runtime_error("Cannot deposit negative.");
    }

    std::lock_guard<std::mutex> lock(_mtx);

    if (!_isopen) {
        throw std::runtime_error("Account not opened.");
    }
    _balance += amount;
}

void Bankaccount::withdraw(balance_t amount) {
    if (amount < 0) {
        throw std::runtime_error("Withdraw too high or negative");
    }

    std::lock_guard<std::mutex> lock(_mtx);

    if (!_isopen) {
        throw std::runtime_error("Account not opened.");
    }
    if (amount > _balance) {
        throw std::runtime_error("Withdraw too high or negative");
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