//
// Created by filip on 18.06.23.
//

#ifndef CPU_USAGE_TRACKER_WATCHDOG_H
#define CPU_USAGE_TRACKER_WATCHDOG_H

#include "global_variables.h"

void *watchdog(void*);

extern pthread_mutex_t watchdog_mutex;
extern pthread_cond_t watchdogCond;

extern int Threads_Table[NR_OF_THREADS];

#endif //CPU_USAGE_TRACKER_WATCHDOG_H
