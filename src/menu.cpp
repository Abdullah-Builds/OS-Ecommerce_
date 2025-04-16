#include "menu.h"
#include "Inventory.h"
#include<iostream>
#include<unistd.h>
using namespace std;

void menu() {
    int ch;

    cout << "\n====== Inventory Menu ======" << endl;
    cout << "1. Add Inventory" << endl;
    cout << "2. Update Inventory" << endl;
    cout << "3. Display Inventory" << endl;
    cout << "4. Remove Inventory" << endl;
    cout << "Enter your choice: ";
    cin >> ch;
    
    Inventory inventory;

    switch (ch) {
        case 1:
            inventory.Add_Inventory();
            break;
        case 2:
            inventory.Update_Inventory();
            break;
        case 3:
            inventory.Display_Inventory();
            break;
        case 4:
            inventory.Remove_Inventory();
            break;
        default:
            cout << "You have missed your chance. Invalid option!" << endl;
            break;
    }
}

