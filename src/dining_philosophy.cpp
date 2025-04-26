#include "dining_philosophy.h"
#include <random>
#include <chrono>
#include <thread>
#include "menu.h"

using namespace std;

binary_semaphore forks[NUM_PHILOSOPHERS] = {
    binary_semaphore(1), binary_semaphore(1), binary_semaphore(1),
    binary_semaphore(1), binary_semaphore(1), binary_semaphore(1),
    binary_semaphore(1), binary_semaphore(1), binary_semaphore(1),
    binary_semaphore(1)
};


atomic<bool> philosopher_active[NUM_PHILOSOPHERS];
mutex cout_mutex;
mutex cin_mutex;

condition_variable cv;
int current_philosopher = 0;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dist(1, 3);

void think() {
    this_thread::sleep_for(chrono::seconds(dist(gen)));
}

void eat() {
    this_thread::sleep_for(chrono::seconds(dist(gen)));
}

void menu_and_wait(int id) {
    int turn;
    {
        lock_guard<mutex> input_lock(cin_mutex);
        cout << "\nPhilosopher " << id << ",  ( any number to continue): ";
        cin >> turn;
    }

    menu();
    
    {
        lock_guard<mutex> lock(cout_mutex);
        cout << "Menu interaction completed for Philosopher " << id << endl;
    }
}

void* philosopher(void* arg) {
    int id = *(int*)arg;
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    while (philosopher_active[id]) {
       
        {
            unique_lock<mutex> ul(cout_mutex);
            cv.wait(ul, [id] { return current_philosopher == id; });
        }

        menu_and_wait(id);

        {
            lock_guard<mutex> lock(cout_mutex);
            current_philosopher = (current_philosopher + 1) % NUM_PHILOSOPHERS;
            cv.notify_all();
        }

        {
            lock_guard<mutex> lock(cout_mutex);
            cout << "Philosopher " << id << " is thinking." << endl;
        }

        think();

       
        if (id % 2 == 0) {
            forks[left].acquire();
            forks[right].acquire();
        } else {
            forks[right].acquire();
            forks[left].acquire();
        }

        {
            lock_guard<mutex> lock(cout_mutex);
            cout << "Philosopher " << id << " is eating." << endl;
        }

        eat(); 

        forks[left].release();
        forks[right].release();
    }

    {
        lock_guard<mutex> lock(cout_mutex);
        cout << "Philosopher " << id << " has exited." << endl;
    }

    
    return nullptr;
}
