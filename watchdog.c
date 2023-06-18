//
// Created by filip on 18.06.23.
//

#include "watchdog.h"

void thread_is_working(int Thread_nr)
{
    pthread_mutex_lock(&watchdog_mutex);
    Threads_Table[Thread_nr] = 1;
    pthread_mutex_unlock(&watchdog_mutex);
}

void *watchdog(void*)
{
    while(!done) {
        sleep(WATCHDOG_TIMEOUT);
        pthread_mutex_lock(&watchdog_mutex);
        for (int i = 0; i < NR_OF_THREADS; i++) {
            if (Threads_Table[i] == 0) {
                term(0);
            }
            Threads_Table[i] = 0;
        }
        pthread_mutex_unlock(&watchdog_mutex);
    }
    pthread_mutex_unlock(&watchdog_mutex);

}