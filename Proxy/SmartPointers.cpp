/**
 * Smart pointers are an example of a proxy.
 */

#include <iostream>
#include <iomanip>
#include <memory>

struct BankAccount {
    virtual ~BankAccount() = default;
    virtual void deposit(int amount) = 0;
    virtual void withdraw(int amount) = 0;
};

struct CurrentAccount : BankAccount {
    explicit CurrentAccount(const int balance) : balance{balance} {}

    void deposit(int amount) override {
        balance += amount;
    }

    void withdraw(int amount) override {
        if (amount <= balance) balance -= amount;
    }

    friend std::ostream &operator<<(std::ostream &os, const CurrentAccount &account) {
        os << " balance: " << account.balance;
        return os;
    }

private:
    int balance;
};

int main() {
    BankAccount *a = new CurrentAccount{123};
    a->deposit(321);
    delete a;

    // When you use a smart pointer, you get something that essentially behaves like a pointer, but has more features.
    // Thus, a proxy.
    auto b = std::make_shared<CurrentAccount>(123);
    b->deposit(123);
    BankAccount *actual = b.get();
    actual->withdraw(123);

    if (b) {
        std::cout << "Bank account exists!" << std::endl;
        std::cout << *b << std::endl;
    }

    std::cout << std::boolalpha << *dynamic_cast<CurrentAccount*>(actual) << std::endl;

}