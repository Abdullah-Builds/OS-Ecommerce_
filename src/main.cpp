#include <iostream>
<<<<<<< HEAD
#include <pthread.h>
#include "dining_philosophy.h"
#include "loader.h"
#include<unistd.h>

using namespace std;  

int main() {
    Intro();
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosopher_active[i] = true;
        ids[i] = i;
        pthread_create(&philosophers[i], nullptr, philosopher, &ids[i]);
        sleep(3);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_join(philosophers[i], nullptr);
    }

    cout << "All philosophers have exited. Program ending." << endl;
    return 0;
}
=======
#include <vector>
#include <thread>
#include <chrono>
#include <string>
#include <map>
#include "inventory.h"
#include "customer.h"
#include "auth.h"
#include "admin.h"
#include "dining_philosophers.h"

void runInventorySystem()
{
    std::cout << "\n=== Starting E-Commerce Inventory Management System ===\n"
              << std::endl;

    Inventory inventory;
    Auth auth;
    Admin admin(inventory);
    std::map<std::string, Customer *> customers;

    // Initialize some products
    inventory.addProduct("P1", 50);
    inventory.addProduct("P2", 30);
    inventory.addProduct("P3", 20);
    inventory.addProduct("P4", 40);
    inventory.addProduct("P5", 25);

    char choice;
    bool loggedIn = false;
    std::string currentUser;
    bool isAdmin = false;

    while (true)
    {
        if (!loggedIn)
        {
            std::cout << "\n1. Register" << std::endl;
            std::cout << "2. Login" << std::endl;
            std::cout << "3. Admin Login" << std::endl;
            std::cout << "4. Exit" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice)
            {
            case '1':
            {
                std::string username, password;
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter password: ";
                std::cin >> password;

                if (auth.registerUser(username, password))
                {
                    std::cout << "Registration successful!" << std::endl;
                }
                else
                {
                    std::cout << "Username already exists!" << std::endl;
                }
                break;
            }
            case '2':
            {
                std::string username, password;
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter password: ";
                std::cin >> password;

                if (auth.login(username, password))
                {
                    loggedIn = true;
                    currentUser = username;
                    std::string userId = auth.getUserId(username);
                    customers[currentUser] = new Customer(userId, username, inventory);
                    customers[currentUser]->start();
                    std::cout << "Login successful!" << std::endl;
                }
                else
                {
                    std::cout << "Invalid credentials!" << std::endl;
                }
                break;
            }
            case '3':
            {
                std::string username, password;
                std::cout << "Enter admin username: ";
                std::cin >> username;
                std::cout << "Enter admin password: ";
                std::cin >> password;

                if (admin.login(username, password))
                {
                    loggedIn = true;
                    isAdmin = true;
                    std::cout << "Admin login successful!" << std::endl;
                }
                else
                {
                    std::cout << "Invalid admin credentials!" << std::endl;
                }
                break;
            }
            case '4':
                std::cout << "Exiting..." << std::endl;
                return;
            default:
                std::cout << "Invalid choice!" << std::endl;
            }
        }
        else if (isAdmin)
        {
            std::cout << "\nAdmin Menu:" << std::endl;
            std::cout << "1. View Inventory" << std::endl;
            std::cout << "2. Add Product" << std::endl;
            std::cout << "3. Update Stock" << std::endl;
            std::cout << "4. View All Orders" << std::endl;
            std::cout << "5. Approve Order" << std::endl;
            std::cout << "6. Reject Order" << std::endl;
            std::cout << "7. Logout" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice)
            {
            case '1':
                admin.displayInventory();
                break;
            case '2':
            {
                std::string productId;
                int quantity;
                std::cout << "Enter product ID: ";
                std::cin >> productId;
                std::cout << "Enter quantity: ";
                std::cin >> quantity;

                if (admin.addProduct(productId, quantity))
                {
                    std::cout << "Product added successfully!" << std::endl;
                }
                else
                {
                    std::cout << "Product already exists!" << std::endl;
                }
                break;
            }
            case '3':
            {
                std::string productId;
                int quantity;
                std::cout << "Enter product ID: ";
                std::cin >> productId;
                std::cout << "Enter new quantity: ";
                std::cin >> quantity;

                if (admin.updateStock(productId, quantity))
                {
                    std::cout << "Stock updated successfully!" << std::endl;
                }
                else
                {
                    std::cout << "Product not found or invalid quantity!" << std::endl;
                }
                break;
            }
            case '4':
            {
                auto orders = admin.getAllOrders();
                std::cout << "\nAll Orders:" << std::endl;
                for (const auto &order : orders)
                {
                    std::cout << "Order ID: " << order.orderId
                              << ", User ID: " << order.userId
                              << ", Product: " << order.productId
                              << ", Quantity: " << order.quantity
                              << ", Approved: " << (order.approved ? "Yes" : "No") << std::endl;
                }
                break;
            }
            case '5':
            {
                std::string orderId;
                std::cout << "Enter order ID to approve: ";
                std::cin >> orderId;

                if (admin.approveOrder(orderId))
                {
                    std::cout << "Order approved successfully!" << std::endl;
                }
                else
                {
                    std::cout << "Order not found or cannot be approved!" << std::endl;
                }
                break;
            }
            case '6':
            {
                std::string orderId;
                std::cout << "Enter order ID to reject: ";
                std::cin >> orderId;

                if (admin.rejectOrder(orderId))
                {
                    std::cout << "Order rejected successfully!" << std::endl;
                }
                else
                {
                    std::cout << "Order not found or already approved!" << std::endl;
                }
                break;
            }
            case '7':
                loggedIn = false;
                isAdmin = false;
                std::cout << "Logged out successfully!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice!" << std::endl;
            }
        }
        else
        {
            std::cout << "\nCustomer Menu:" << std::endl;
            std::cout << "1. View Inventory" << std::endl;
            std::cout << "2. View My Orders" << std::endl;
            std::cout << "3. Logout" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice)
            {
            case '1':
            {
                auto currentInventory = inventory.getInventory();
                std::cout << "\nCurrent Inventory:" << std::endl;
                for (const auto &item : currentInventory)
                {
                    std::cout << "Product " << item.first << ": " << item.second << " units" << std::endl;
                }
                break;
            }
            case '2':
            {
                auto orders = customers[currentUser]->getOrders();
                std::cout << "\nMy Orders:" << std::endl;
                for (const auto &order : orders)
                {
                    std::cout << "Order ID: " << order.orderId
                              << ", Product: " << order.productId
                              << ", Quantity: " << order.quantity
                              << ", Approved: " << (order.approved ? "Yes" : "No") << std::endl;
                }
                break;
            }
            case '3':
                customers[currentUser]->stop();
                delete customers[currentUser];
                customers.erase(currentUser);
                loggedIn = false;
                std::cout << "Logged out successfully!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice!" << std::endl;
            }
        }
    }
}

void runDiningPhilosophers()
{
    std::cout << "\n=== Starting Dining Philosophers Simulation ===\n"
              << std::endl;

    DiningPhilosophers dp;
    dp.start();

    // Let the simulation run for a while
    std::this_thread::sleep_for(std::chrono::seconds(10));

    dp.stop();
}

int main()
{
    char choice;

    while (true)
    {
        std::cout << "\nE-Commerce Inventory Management System" << std::endl;
        std::cout << "1. Run Inventory Management System" << std::endl;
        std::cout << "2. Run Dining Philosophers Simulation" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter your choice (1-3): ";
        std::cin >> choice;

        switch (choice)
        {
        case '1':
            runInventorySystem();
            break;
        case '2':
            runDiningPhilosophers();
            break;
        case '3':
            std::cout << "Exiting program..." << std::endl;
            return 0;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}
>>>>>>> 7b5267bdf70d647e51f341d4d171039958798624
