#include <string>

using namespace std;

#ifndef _CUSTOMER_H
#define _CUSTOMER_H

class Customer {
private:
    string name;
    string phoneNo;
    int balance;

public:
    Customer(string name, string phoneNo, int balance) {
        this -> name = name;
        this -> phoneNo = phoneNo;
        this -> balance = balance;
    }

    const string &getName() const {
        return name;
    }

    const string &getPhoneNo() const {
        return phoneNo;
    }

    int getBalance() const {
        return balance;
    }

    string addMoney(int money) {
        balance += money;
        return "Money added successfully.";
    }

    string pay(int amount) {
        if (balance < amount) {
            return "Not enough money to buy.";
        } else {
            balance -= amount;
            return "Payment Successful";
        }
    }
};

#endif