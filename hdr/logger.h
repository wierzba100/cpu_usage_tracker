#ifndef CPU_USAGE_TRACKER_LOGGER_H
#define CPU_USAGE_TRACKER_LOGGER_H

#include "global_variables.h"

extern pthread_mutex_t lock;
extern pthread_mutex_t watchdog_mutex;
extern pthread_cond_t analyzerCond;
extern pthread_cond_t watchdogCond;

extern sem_t emptyReaderBuffer;
extern sem_t fullReaderBuffer;

extern int Threads_Table[NR_OF_THREADS];

void *logger(void*);

#endif //CPU_USAGE_TRACKER_LOGGER_H
