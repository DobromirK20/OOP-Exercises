#include <iostream>
#include <cstring>
using namespace std;

class BankAccount
{
private:
    double* transactions;
    int size;
    int capacity;

    void resize() {
        capacity *= 2;
        double* newTransactions = new double[capacity];

        for(int i = 0; i < size; i++) {
            newTransactions[i] = transactions[i];
        }

        delete[] transactions;
        transactions = newTransactions;
    }

    void copyFrom(const BankAccount& other) {
        size = other.size;
        capacity = other.capacity;

        transactions = new double[capacity];
        for(int i = 0; i < size; i++) {
            transactions[i] = other.transactions[i];
        }
    }

    void free() {
        delete[] transactions;
    }

public:
    BankAccount() : size(0), capacity(4) {
        transactions = new double[capacity];
    }

    BankAccount(const BankAccount& other) {
        copyFrom(other);
    }

    BankAccount& operator=(const BankAccount& other) {
        if(this != &other) {
            free();
            copyFrom(other);
        }

        return *this;
    }

    ~BankAccount() {
        free();
    }

    void deposit(double amount) {
        if(amount <= 0) {
            cout << "Invalid deposit amount!" << endl;
            return;
        }

        if(size >= capacity) {
            resize();
        }

        transactions[size++] = amount;
    }

    void withdraw(double amount) {
        if(amount <= 0) {
            cout << "Invalid withdraw amount!" << endl;
            return;
        }

        if(size >= capacity) {
            resize();
        }

        if(amount > getBalance()) {
            cout << "Insufficient funds!" << endl;
            return;
        }

        transactions[size++] = -amount;
    }

    double getBalance() const {
        double balance = 0;

        for(int i = 0; i < size; i++) {
            balance += transactions[i];
        }

        return balance;
    }

    void printHistory() const {
        cout << "Transaction history: ";
        for (int i = 0; i < size; i++) {
            if (i > 0) {
                cout << ", ";
            }
            cout << transactions[i];
        }
        cout << endl;
    }
};

int main() {
    BankAccount acc;

    acc.deposit(1000);
    acc.withdraw(200);
    acc.deposit(300);
    acc.withdraw(100);

    cout << "Original account:" << endl;
    acc.printHistory();
    cout << "Balance: " << acc.getBalance() << endl;

    BankAccount copyAcc = acc;
    copyAcc.deposit(500);
    copyAcc.withdraw(50);

    cout << "\nCopied account after changes:" << endl;
    copyAcc.printHistory();
    cout << "Balance: " << copyAcc.getBalance() << endl;

    cout << "\nOriginal account after copy changes:" << endl;
    acc.printHistory();
    cout << "Balance: " << acc.getBalance() << endl;

    return 0;
}