//
// Created by filip on 18.06.23.
//

#ifndef GPU_USAGE_TRACKER_LOGGER_H
#define GPU_USAGE_TRACKER_LOGGER_H

#include "global_variables.h"

extern pthread_mutex_t lock;
extern pthread_mutex_t watchdog_mutex;
extern pthread_cond_t analyzerCond;
extern pthread_cond_t watchdogCond;

extern int Threads_Table[NR_OF_THREADS];

void *logger(void*);

#endif //GPU_USAGE_TRACKER_LOGGER_H
