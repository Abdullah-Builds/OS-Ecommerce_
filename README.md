# E-Commerce Inventory Management System

## Project Overview

This project simulates an online store's inventory management system using concurrent programming concepts. It demonstrates various operating system concepts including:

- Process Synchronization (Mutexes and Semaphores)
- Deadlock Avoidance
- Shared Resource Management
- Concurrent Data Access
- Dining Philosophers Problem

## Features

- User registration and authentication
- Admin panel for inventory management
- Customer order placement and tracking
- Concurrent customer order processing
- Inventory management with thread-safe operations
- Stock threshold monitoring
- Order approval system
- Dining Philosophers implementation

## Project Structure

OS-Ecommerce/
│
├── README.md
├── makefile
│
├── include/
│   ├── auth.h
│   ├── dining_philosophy.h
│   ├── inventory.h
│   ├── loader.h
│   ├── menu.h
│
├── src/
│   ├── auth.cpp
│   ├── dining_philosophy.cpp
│   ├── inventory.cpp
│   ├── loader.cpp
│   ├── main.cpp
│   ├── menu.cpp
│
├── database/
│   ├── inventory.db
│   ├── users.db
│
├── notes/
│   ├── Instructions.txt
│   ├── Workflow.png
│
└── initializer/
    ├── Initialize_Inventory_db.cpp
    ├── User_Initializer_db.cpp


## Building and Running

1. Compile the project:
   ```bash
   make
   ```
2. Run the main program:
   ```bash
   ./app
   ```

## Usage

### Customer Features

-Authentication
-Add to Inventory
-Display your Inventory
-Update Inventory
-Delete Inventory

### Dining Philosophers Simulation

- Demonstrates deadlock prevention in resource allocation
- Shows the state of each philosopher (thinking/eating)

## Implementation Details

- Uses POSIX threads for concurrent operations
- Implements mutex for inventory updates
- Uses semaphores for stock control
- Database(sqlite)
- Demonstrates deadlock prevention in resource allocation
- Thread-safe user authentication
- Concurrent order processing
