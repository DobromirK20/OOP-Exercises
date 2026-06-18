#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
using namespace std;

class BankException : public runtime_error
{
public:
    BankException(const string& mes) : runtime_error(mes) {}
};

class InvalidAmountException : public BankException
{
public:
    InvalidAmountException()
        : BankException("Invalid amount") {}
};

class InsufficientFundsException : public BankException
{
public:
    InsufficientFundsException()
        : BankException("Insufficient funds") {}
};

class AccountNotFind : public BankException
{
public:
    AccountNotFind() : BankException("Account not find"){}
};


class BankAccount
{
private:
    string name;
    double balance;
public:
    BankAccount(const string& n, double b) : name(n), balance(b) {}

    void deposit(double sum) {
        if(sum < 0) {
            throw InvalidAmountException();
        }

        balance += sum;
    }

    void withdraw(double sum) {
        if(sum < 0) {
            throw InvalidAmountException();
        }

        if(balance < sum) {
            throw InsufficientFundsException();
        }

        balance -= sum;
    }

    string getName() const {
        return name;
    }

    BankAccount* clone() const {
        return new BankAccount(*this);
    }

    void print() const {
        cout << name << ": " << balance << endl;
    }
};

class Bank
{
private:
    vector<BankAccount*> accounts;
public:
    Bank() {}

    void add(const BankAccount& a) {
        accounts.push_back(a.clone());
    }

    Bank(const Bank& other) {
        for(BankAccount* a : other.accounts) {
            accounts.push_back(a->clone());
        }
    }

    Bank& operator=(const Bank& other) {
        if(this != &other) {
            for(BankAccount* a : accounts) {
                delete a;
            }

            accounts.clear();

            for(BankAccount* a : other.accounts) {
                accounts.push_back(a->clone());
            }
        }

        return *this;
    }

    BankAccount* findAccount(string n) {
        for(BankAccount* a : accounts) {
            if(a->getName() == n) {
                return a;
            }
        }

        throw AccountNotFind();
    }

    ~Bank() {
        for(BankAccount* a : accounts) {
            delete a;
        }
    }
};

int main()
{
    try
    {
        Bank bank;

        BankAccount ivan("Ivan", 1000);
        BankAccount maria("Maria", 500);
        BankAccount petar("Petar", 200);

        bank.add(ivan);
        bank.add(maria);
        bank.add(petar);

        cout << "Accounts added successfully." << endl;

        BankAccount b1("Test", 100);

        b1.deposit(50);
        b1.print();

        b1.withdraw(30);
        b1.print();

        BankAccount* acc = bank.findAccount("Ivan");
        acc->deposit(100);
        acc->print();

        b1.withdraw(500); // тук ще хвърли изключение
        b1.print();
    }
    catch(const BankException& e)
    {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}


