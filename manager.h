#include <string>
#include <algorithm>

#include "reception.h"
#include "item.h"
#include "bill.h"

using namespace std;

#ifndef _MANAGER_H
#define _MANAGER_H

class Manager {
public:
    string addItem(Item item) {
        Reception::items.push_back(item);
        return "Added the item successfully.";
    }

    string removeItem(int id) {
        auto pos = Reception::getItemById(id);
        if (pos == Reception::items.end()) {
            return "Item not found.";
        }
        Reception::items.erase(pos);
        return "Item successfully removed.";
    }

    string addCash(int cash) {
        Reception::cash += cash;
        return "Added cash successfully.";
    }

    string updatePrice(int id, int newPrice) {
        auto pos = Reception::getItemById(id);
        if (pos == Reception::items.end()) {
            return "Item not found.";
        }
        pos -> setPrice(newPrice);
        return "Successfully updated price of the item.";
    }

    string updateStocks(int id, int noOfStocks, string action) {
        auto pos = Reception::getItemById(id);
        if (pos == Reception::items.end()) {
            return "Item not found.";
        }
        int oldNoOfStocks = pos -> getStockCount();
        if (action == "Add") {
            pos -> setStockCount(oldNoOfStocks + noOfStocks);
        } else if (action == "Remove") {
            pos -> setStockCount(oldNoOfStocks - noOfStocks);
        } else {
            return "Invalid action.";
        }
        return "Successfully updated stock count of the item.";
    }

    Item getItemFromCanteen(string &name) {
        return Reception::getItemByName(name);
    }

    Bill generateBill(string phoneNo, vector<pair<Item, int>> &buyingList) {
        Bill bill(phoneNo, buyingList);
        return bill;
    }

    string saveBill(Bill bill) {
        Reception::bills.push_back(bill);
        return "Bill saved successfully.";
    }

    int getReceptionBalance() {
        return Reception::cash;
    }

    const vector<Bill> &getAllBills() {
        return Reception::getBills();
    }
};

#endif
