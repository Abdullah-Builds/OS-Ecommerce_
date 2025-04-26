#include <iostream>
#include <pthread.h>
#include "dining_philosophy.h"
#include "loader.h"
#include <unistd.h>

using namespace std;

int main() {
    Intro();

    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        ids[i] = i;
        if (pthread_create(&philosophers[i], nullptr, philosopher, &ids[i]) != 0) {
            cout << "Error creating thread for philosopher " << i << endl;
            return -1;
        }
    }

    pthread_mutex_lock(&cv_mutex);
    current_philosopher = 0;
    pthread_cond_broadcast(&cv);
    pthread_mutex_unlock(&cv_mutex);

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_join(philosophers[i], nullptr);
    }

    cout << "All philosophers have exited. Program ending." << endl;
    return 0;
}
#include <iostream>
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
   
