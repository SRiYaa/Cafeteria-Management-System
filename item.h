#include <string>

using namespace std;

#ifndef _ITEM_H
#define _ITEM_H

class Item {
private:
    static int lastId;
    int id;
    string name;
    int price;
    int stockCount;

    static int getAnId() {
        Item::lastId++;
        return Item::lastId;
    }

public:
    Item() {
        id = -1;
    }

    Item(string name, int price, int stockCount = 0) {
        this -> id = getAnId();
        this -> name = name;
        this -> price = price;
        this -> stockCount = stockCount;
    }

    int getId() const {
        return id;
    }

    const string &getName() const {
        return name;
    }

    int getPrice() const {
        return price;
    }

    void setPrice(int price) {
        this -> price = price;
    }

    int getStockCount() const {
        return stockCount;
    }

    void setStockCount(int stockCount) {
        this -> stockCount = stockCount;
    }
};

#endif