#include "bank_account.h"

#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : _isopen(false) {}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(_mtx);

    if (!_isopen) {
        _isopen = true;
        _balance = 0;
    } else throw std::runtime_error("Account not opened.");

}

void Bankaccount::deposit(balance_t amount) {

    std::lock_guard<std::mutex> lock(_mtx);

    if (_isopen) {
        if (amount >= 0) _balance += amount;
        else throw std::runtime_error("Cannot deposit negative.");
    }
    else throw std::runtime_error("Account not opened.");
}
void Bankaccount::withdraw(balance_t amount) {

    std::lock_guard<std::mutex> lock(_mtx);

    if (_isopen) {
        if (amount <= _balance && amount >= 0) {
            _balance -= amount;
        } else throw std::runtime_error("Withdraw too high or negative");
    } else throw std::runtime_error("Account not opened.");

}
balance_t Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(_mtx);

    if (_isopen) return _balance;
    else throw std::runtime_error("Account not opened.");
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(_mtx);
    if (_isopen) {
        _isopen = false;
        _balance = 0;
    } else throw std::runtime_error("Account not opened.");
    
}


}