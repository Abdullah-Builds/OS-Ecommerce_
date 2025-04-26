#include "dining_philosophy.h"
#include <random>
#include <chrono>
#include <thread>
#include <pthread.h>
#include "menu.h"

using namespace std;

binary_semaphore forks[NUM_PHILOSOPHERS] = {
    binary_semaphore(1), binary_semaphore(1), binary_semaphore(1),
    binary_semaphore(1), binary_semaphore(1), binary_semaphore(1),
    binary_semaphore(1), binary_semaphore(1), binary_semaphore(1),
    binary_semaphore(1)
};

atomic<bool> philosopher_active[NUM_PHILOSOPHERS];

pthread_mutex_t cout_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t cin_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t cv_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;

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

    pthread_mutex_lock(&cin_mutex);
    cout << "\nPhilosopher " << id << ", do you want to exit for next time? (-1 to exit, any other number to continue): ";
    cin >> turn;
    pthread_mutex_unlock(&cin_mutex);

    if (turn == -1) {
        philosopher_active[id] = false;
    }

    menu();

    pthread_mutex_lock(&cout_mutex);
    cout << "Menu interaction completed for Philosopher " << id << endl;
    pthread_mutex_unlock(&cout_mutex);
}

void* philosopher(void* arg) {
    int id = *(int*)arg;
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    while (philosopher_active[id]) {
        pthread_mutex_lock(&cv_mutex);
        while (current_philosopher != id) {
            pthread_cond_wait(&cv, &cv_mutex);
        }
        pthread_mutex_unlock(&cv_mutex);

        menu_and_wait(id);

        pthread_mutex_lock(&cv_mutex);
        current_philosopher = (current_philosopher + 1) % NUM_PHILOSOPHERS;
        pthread_cond_broadcast(&cv);
        pthread_mutex_unlock(&cv_mutex);

        pthread_mutex_lock(&cout_mutex);
        cout << "Philosopher " << id << " is thinking." << endl;
        pthread_mutex_unlock(&cout_mutex);

        think();

        if (id % 2 == 0) {
            forks[left].acquire();
            forks[right].acquire();
        } else {
            forks[right].acquire();
            forks[left].acquire();
        }

        pthread_mutex_lock(&cout_mutex);
        cout << "Philosopher " << id << " is eating." << endl;
        pthread_mutex_unlock(&cout_mutex);

        eat();

        forks[left].release();
        forks[right].release();
    }

    pthread_mutex_lock(&cout_mutex);
    cout << "Philosopher " << id << " has exited." << endl;
    pthread_mutex_unlock(&cout_mutex);

    return nullptr;
}
