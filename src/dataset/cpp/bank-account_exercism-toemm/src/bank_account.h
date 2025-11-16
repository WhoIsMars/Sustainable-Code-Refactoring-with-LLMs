#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>

namespace Bankaccount {

using balance_t = int;

class Bankaccount {  // class Bankaccount

    public:
    Bankaccount();

    void open();
    void deposit(balance_t amount);
    void withdraw(balance_t amount);
    balance_t balance() const;

    void close();


    private:
    bool _isopen;
    balance_t _balance;
    mutable std::mutex _mtx;


};

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H