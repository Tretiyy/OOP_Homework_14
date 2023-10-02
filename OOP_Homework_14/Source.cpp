#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Account {
public:
    Account(int number, double balance) : account_no(number), balance(balance) {}

    virtual void deposit(double amount) {
        balance += amount;
    }

    virtual void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
        }
        else {
            cout << "Insufficient balance." << endl;
        }
    }

    virtual void createTransaction(int transaction_id, double amount, std::string type) {
        //
    }

    double balance;
private:
    int account_no;
};

class CurrentAccount : public Account {
public:
    CurrentAccount(int number, double balance) : Account(number, balance) {}
};

class SavingsAccount : public Account {
public:
    SavingsAccount(int number, double balance) : Account(number, balance) {}
};

class ATM_Transactions {
public:
    ATM_Transactions(int transaction_id, string date, string type, double amount, double post_balance)
        : transaction_id(transaction_id), date(date), type(type), amount(amount), post_balance(post_balance) {}

    void modifies(Account& account) {
        if (type == "withdraw") {
            account.withdraw(amount);
        }
        else if (type == "deposit") {
            account.deposit(amount);
        }
        account.createTransaction(transaction_id, amount, type);
    }

private:
    int transaction_id;
    string date;
    string type;
    double amount;
    double post_balance;
};

// Define Customer class
class Customer {
public:
    Customer(string name, string address, string dob, string card_number, int pin)
        : name(name), address(address), dob(dob), card_number(card_number), pin(pin) {}

    bool verify_password(int entered_pin) {
        return pin == entered_pin;
    }

private:
    string name;
    string address;
    string dob;
    string card_number;
    int pin;
};

class ATM {
public:
    ATM(string location, string managedby) : location(location), managedby(managedby) {}

    void identifies(Customer& customer, Account& account) {
        int entered_pin;
        cout << "Enter your PIN: ";
        cin >> entered_pin;

        if (customer.verify_password(entered_pin)) {
            double amount;
            string transaction_type;
            cout << "Enter transaction type (deposit/withdraw): ";
            cin >> transaction_type;
            cout << "Enter transaction amount: ";
            cin >> amount;
            ATM_Transactions transaction(1, "2023-10-02", transaction_type, amount, account.balance);
            transaction.modifies(account);
            cout << "Transaction successful. Updated balance: " << account.balance << endl;
        }
        else {
            cout << "Invalid PIN. Transaction aborted." << endl;
        }
    }

    void transactions() {
        //
    }

private:
    string location;
    string managedby;
};

class Bank {
public:
    Bank(string code, string address) : code(code), address(address) {}

    void manages(Account& account, Customer& customer) {
        //
    }

    void maintains(ATM& atm) {
        //
    }

private:
    string code;
    string address;
};

int main() {
    Bank bank("Leiptzig Bank", "boul. Fauerbrehen, 12");
    Customer customer("Michael Bloomkwist", "str. Uberwallen, 59/19", "01.01.2000", "1234567890", 1234);
    SavingsAccount savings_account(1, 1000);
    bank.manages(savings_account, customer);
    ATM atm("ATM_14", "Leiptzig Bank");
    bank.maintains(atm);
    atm.identifies(customer, savings_account);

    system("pause");

    return 0;
}