//
// Created by filip on 18.06.23.
//

#include "watchdog.h"

void thread_is_working(int thread_nr)
{
    pthread_mutex_lock(&watchdog_mutex);
    Threads_Table[thread_nr] = 1;
    pthread_mutex_unlock(&watchdog_mutex);
}

void *watchdog(__attribute__((unused)) void* paramIn)
{
    while(!done) {
        sleep(WATCHDOG_TIMEOUT);
        pthread_mutex_lock(&watchdog_mutex);
        for (int i = 0; i < NR_OF_THREADS; i++) {
            if (Threads_Table[i] == 0) {
                printf("WATCHDOG ALERT: Zawiesił się %d watek\n", i);
                printf("Closing program... WATCHDOG ERROR\n");
                Threads_Table[i] = -1;
                exit(-1);
            }else {
                Threads_Table[i] = 0;
            }
        }
        pthread_mutex_unlock(&watchdog_mutex);
        pthread_cond_signal(&watchdogCond);
    }
    return NULL;
}