//
// Created by filip on 18.06.23.
//

#ifndef GPU_USAGE_TRACKER_WATCHDOG_H
#define GPU_USAGE_TRACKER_WATCHDOG_H

#include "global_variables.h"

void *watchdog(void*);

extern pthread_mutex_t watchdog_mutex;

extern bool Threads_Table[NR_OF_THREADS];

#endif //GPU_USAGE_TRACKER_WATCHDOG_H
