#include <string>
#include <vector>
#include <algorithm>

#include "item.h"
#include "bill.h"

using namespace std;

#ifndef _RECEPTION_H
#define _RECEPTION_H

class Reception {
private:
    static int cash;
    static vector<Item> items;
    static vector<Bill> bills;

    static const vector<Bill> &getBills() {
        return bills;
    }

    static auto getItemById(int id) {
        auto pos = find_if(items.begin(), items.end(), [&id](const Item &item) {
            return item.getId() == id;
        });
        return pos;
    }

    static Item getItemByName(string &name) {
        Item item;
        for (int i = 0; i < items.size(); ++i) {
            if (items[i].getName() == name) {
                item = items[i];
            }
        }
        return item;
    }

public:
    friend class Manager;

    static const vector<Item> &getMenu() {
        return items;
    }
};

#endif