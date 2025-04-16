#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
using namespace std;

class Inventory
{
private:
    string item;
    double price;
    int quantity;
    string name;
public:
    void Add_Inventory();
    void Update_Inventory();
    void Display_Inventory();
    void Remove_Inventory();
};

#endif
