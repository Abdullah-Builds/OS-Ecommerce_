
# E-Commerce Inventory Management System

## Project Overview

This project simulates an online store's inventory management system using concurrent programming principles. It demonstrates key operating system concepts including:

* Process Synchronization (Mutexes and Semaphores)
* Deadlock Avoidance
* Shared Resource Management
* Concurrent Data Access
* Dining Philosophers Problem Simulation

## Features

* User registration and authentication
* Admin panel for inventory management
* Customer order placement and tracking
* Concurrent order processing
* Thread-safe inventory management
* Stock threshold monitoring and alerts
* Order approval system
* Dining Philosophers deadlock prevention demonstration

## Project Structure

```
OS-Ecommerce/
├── README.md
├── makefile
├── include/
│   ├── auth.h
│   ├── dining_philosophy.h
│   ├── inventory.h
│   ├── loader.h
│   └── menu.h
├── src/
│   ├── auth.cpp
│   ├── dining_philosophy.cpp
│   ├── inventory.cpp
│   ├── loader.cpp
│   ├── main.cpp
│   └── menu.cpp
├── database/
│   ├── inventory.db
│   └── users.db
├── notes/
│   ├── Instructions.txt
│   └── Workflow.png
└── initializer/
    ├── Initialize_Inventory_db.cpp
    └── User_Initializer_db.cpp
```

## Building and Running

1. Compile the project:
   ```bash
   make
   ```
2. Run the executable:
   ```bash
   ./app
   ```

## SQLite3 Setup

Ensure SQLite3 and its development libraries are installed:

```bash
sudo apt update
sudo apt install sqlite3 libsqlite3-dev
```

## GUI Tool: DB Browser for SQLite

You can use **DB Browser for SQLite** to manage `.db` files:

```bash
sqlitebrowser
```

* **Open/Create a Database** : Use "Open Database" to load an existing `.db` file.
* **Create Tables** : Go to the "Database Structure" tab and select "Create Table."
* **Add/Edit Data** : Use the "Browse Data" or "Execute SQL" tabs to modify records.
* **Save and Close** : Click "Write Changes" to save, then "Close Database" to exit.

## Usage

### Customer Functions

* Authentication (Login/Register)
* Add items to inventory
* Display inventory
* Update inventory items
* Delete inventory items

### Dining Philosophers Simulation

* Demonstrates deadlock prevention strategies
* Visualizes philosopher states (thinking, eating)

## Implementation Details

* Uses POSIX threads (`pthread`) for concurrent operations
* Inventory updates protected with mutex locks
* Semaphores used for stock threshold control
* SQLite3 for persistent database storage
* Deadlock prevention using classic concurrency techniques
* Thread-safe user authentication and order processing
