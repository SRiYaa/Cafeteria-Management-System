#include <string>
#include <vector>

#include "item.h"

using namespace std;

#ifndef _BILL_H
#define _BILL_H

class Bill {
private:
    static int lastId;

    int id;
    string customerPhoneNo;
    int payAmount;
    vector<pair<Item, int>> boughtItems;

    static int getAnId() {
        lastId++;
        return lastId;
    }

    static int calcPayAmount(vector<pair<Item, int>> &boughtItems) {
        int amount = 0;
        for (pair<Item, int> &p : boughtItems) {
            amount += (p.first).getPrice() * p.second;
        }
        return amount;
    }

public:
    Bill(string customerPhoneNo, vector<pair<Item, int>> &boughtItems) {
        this -> id = getAnId();
        this -> customerPhoneNo = customerPhoneNo;
        this -> payAmount = calcPayAmount(boughtItems);
        this -> boughtItems = boughtItems;
    }

    const string &getCustomerPhoneNo() const {
        return customerPhoneNo;
    }

    int getPayAmount() const {
        return payAmount;
    }

    const vector<pair<Item, int>> &getBoughtItems() const {
        return boughtItems;
    }
};

#endif