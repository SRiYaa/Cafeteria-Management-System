#include <iostream>

#include "manager.h"
#include "item.h"
#include "reception.h"
#include "customer.h"
#include "bill.h"

using namespace std;

int main() {
    Manager manager;
    bool is_menu_closed = false;
    do {
        int user_choice;
        cout << "Welcome to Canteen!\n\n";
        cout << "Press 1 if you are the manager, 2 if you are a customer and 3 to exit: ";
        cin >> user_choice;
        if (user_choice == 1) {
            cout << "Please enter the password for accessing Reception: ";
            string password;
            cin >> password;
            if (password != "Admin@123") {
                cout << "Wrong Password.\n";
                continue;
            }
            cout << "Access Granted.\n";
            int choice;
            do {
                cout << "What do you want to do?\n";
                cout << "Press 1 for adding cash to the reception's balance.\n";
                cout << "Press 2 for adding an item to the canteen.\n";
                cout << "Press 3 for removing an item from the canteen.\n";
                cout << "Press 4 for changing price of an item.\n";
                cout << "Press 5 for adding stocks.\n";
                cout << "Press 6 for viewing reception's balance.\n";
                cout << "Press 7 for viewing all items.\n";
                cout << "Press 8 for viewing all saved bills.\n";
                cout << "Press 9 to exit.\n";
                cin >> choice;
                if (choice == 1) {
                    int amount;
                    cout << "Enter amount to add: ";
                    cin >> amount;
                    cout << manager.addCash(amount) << '\n';
                } else if (choice == 2) {
                    string name;
                    int price;
                    int stockCount;
                    cout << "Enter item's name(string): ";
                    cin >> name;
                    cout << "Enter item's price(integer): ";
                    cin >> price;
                    cout << "Enter item's stock count(integer): ";
                    cin >> stockCount;
                    Item newItem(name, price, stockCount);
                    cout << manager.addItem(newItem) << '\n';
                } else if (choice == 3) {
                    int id;
                    cout << "Enter item's id to remove: ";
                    cin >> id;
                    cout << manager.removeItem(id) << '\n';
                } else if (choice == 4) {
                    int newPrice, id;
                    cout << "Enter id of the item: ";
                    cin >> id;
                    cout << "Enter new price of the item: ";
                    cin >> newPrice;
                    cout << manager.updatePrice(id, newPrice) << '\n';
                } else if (choice == 5) {
                    int stocksToAdd, id;
                    cout << "Enter id of the item: ";
                    cin >> id;
                    cout << "Enter amount of stocks to add: ";
                    cin >> stocksToAdd;
                    cout << manager.updateStocks(id, stocksToAdd, "Add") << '\n';
                } else if (choice == 6) {
                    cout << "Available balance: " << manager.getReceptionBalance() << '\n';
                } else if (choice == 7) {
                    const vector<Item> items = Reception::getMenu();
                    for (const Item &item : items) {
                        cout << "Item: " << item.getName() << ", Id: " << item.getId() << ", Price: " << item.getPrice() << ", Stock count: " << item.getStockCount() << '\n';
                    }
                } else if (choice == 8) {
                    const vector<Bill> &bills = manager.getAllBills();
                    for (const Bill &bill : bills) {
                        cout << "Customer's Phone number: " << bill.getCustomerPhoneNo() << '\n';
                        const vector<pair<Item, int>> &boughtItems = bill.getBoughtItems();
                        for (const pair<Item, int> &p : boughtItems) {
                            cout << "Item: " << p.first.getName() << ", Quantity bought: " << p.second << ", Price: " << p.first.getPrice() << '\n';
                        }
                        cout << "Total amount paid: " << bill.getPayAmount() << '\n';
                        cout << "-------------------------------------\n";
                    }
                } else if (choice == 9) {
                    cout << "Bye.\n";
                } else {
                    cout << "Wrong choice.\n";
                }
            } while (choice != 9);
        } else if (user_choice == 2) {
            string customerName, phoneNo;
            int balance;
            cout << "Enter your name: ";
            cin >> customerName;
            cout << "Enter your phone number: ";
            cin >> phoneNo;
            cout << "Enter your balance: ";
            cin >> balance;
            Customer customer(customerName, phoneNo, balance);
            int choice;
            do {
                cout << "What do you want to do?\n";
                cout << "Press 1 to get list of items.\n";
                cout << "Press 2 to buy something.\n";
                cout << "Press 3 for adding cash to your balance.\n";
                cout << "Press 4 for viewing your balance.\n";
                cout << "Press 5 to exit.\n";
                cin >> choice;
                if (choice == 1) {
                    const vector<Item> items = Reception::getMenu();
                    for (const Item &item : items) {
                        cout << "Item: " << item.getName() << ", Price: " << item.getPrice() << '\n';
                    }
                } else if (choice == 2) {
                    vector<pair<Item, int>> buyingList;
                    string name;
                    int qty;
                    do {
                        cout << "Enter name of the item to buy or type -1 to go back to the menu: ";
                        cin >> name;
                        if (name == "-1") {
                            break;
                        }
                        Item item = manager.getItemFromCanteen(name);
                        if (item.getId() == -1) {
                            cout << "Item not found.\n";
                            continue;
                        }
                        cout << "Enter quantity: ";
                        cin >> qty;
                        if (qty > item.getStockCount()) {
                            cout << "Not enough stocks\n";
                            continue;
                        }
                        buyingList.emplace_back(item, qty);
                    } while (true);
                    if (!buyingList.empty()) {
                        Bill bill = manager.generateBill(customer.getPhoneNo(), buyingList);
                        string response = customer.pay(bill.getPayAmount());
                        if (response == "Payment Successful") {
                            manager.addCash(bill.getPayAmount());
                            manager.saveBill(bill);
                            for (const pair<Item, int> &p : buyingList) {
                                manager.updateStocks(p.first.getId(), p.second, "Remove");
                            }
                        }
                        cout << response << '\n';
                    }
                } else if (choice == 3) {
                    int money;
                    cout << "Enter amount to add: ";
                    cin >> money;
                    cout << customer.addMoney(money) << '\n';
                } else if (choice == 4) {
                    cout << "Your balance is: " << customer.getBalance() << '\n';
                } else if (choice == 5) {
                    cout << "Bye.\n";
                } else {
                    cout << "Wrong choice.\n";
                }
            } while (choice != 5);
        } else if (user_choice == 3) {
            cout << "Bye.\n";
            is_menu_closed = true;
        } else {
            cout << "Wrong choice!\n";
        }
    } while (!is_menu_closed);
    return 0;
}