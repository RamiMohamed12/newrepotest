#include <iostream>

class BankAccount {
private:
    double balance;

public:
    // Constructor
    BankAccount(double balance) : balance(balance) {}

    // Getter for balance
    double getBalance() const {
        return balance;
    }
    bool deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            return true;
        }
        return false;
    }

    // Withdraw method
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }
};

class Transaction {
private:
    BankAccount* from;
    BankAccount* to;
    double amount;

public:
    // Constructor
    Transaction(BankAccount* from, BankAccount* to, double amount)
        : from(from), to(to), amount(amount) {}

    // Execute method
    bool execute() {
        if (from->withdraw(amount)) { // Withdraw amount from 'from' account
            to->deposit(amount);     // Deposit amount into 'to' account
            return true;
        }
        return false; // Transaction fails if insufficient balance
    }
};

int main() {
    // Create two accounts
    BankAccount* account1 = new BankAccount(1000.0);
    BankAccount* account2 = new BankAccount(500.0);

    // Perform a transaction
    Transaction* transaction = new Transaction(account1, account2, 500.0);
    bool res = transaction->execute();

    if (res) {
        std::cout << "Transaction successful" << std::endl;
    } else {
        std::cout << "Transaction failed" << std::endl;
    }

    std::cout << "Account 1 balance: " << account1->getBalance() << std::endl;
    std::cout << "Account 2 balance: " << account2->getBalance() << std::endl;

    // Clean up transaction object
    delete transaction;

    // Perform another transaction with insufficient funds
    transaction = new Transaction(account1, account2, 5000.0);
    res = transaction->execute();

    if (res) {
        std::cout << "Transaction successful" << std::endl;
    } else {
        std::cout << "Transaction failed" << std::endl;
    }

    std::cout << "Account 1 balance: " << account1->getBalance() << std::endl;
    std::cout << "Account 2 balance: " << account2->getBalance() << std::endl;

    // Clean up memory
    delete transaction;
    delete account1;
    delete account2;

    return 0;
}


