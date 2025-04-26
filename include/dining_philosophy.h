#ifndef DINING_PHILOSOPHY_H
#define DINING_PHILOSOPHY_H

#include <iostream>
#include <pthread.h>
#include <vector>
#include <atomic>
#include <semaphore>
#include <mutex>
#include <condition_variable>

using namespace std;

const int NUM_PHILOSOPHERS = 10;

extern pthread_mutex_t cout_mutex;
extern pthread_mutex_t cin_mutex;
extern pthread_mutex_t cv_mutex;

extern pthread_cond_t cv;

extern binary_semaphore forks[NUM_PHILOSOPHERS];
extern atomic<bool> philosopher_active[NUM_PHILOSOPHERS];

extern int current_philosopher;

void think(int id);
void eat(int id);
void* philosopher(void* arg);
void menu_and_wait(int id);

#endif
