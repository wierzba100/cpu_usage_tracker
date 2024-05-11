#ifndef CPU_USAGE_TRACKER_ANALYZER_H
#define CPU_USAGE_TRACKER_ANALYZER_H

#include "global_variables.h"

void processor_usage(CPU_Data*, CPU_Data*, double*);

void *analyzer(void *);

extern pthread_mutex_t lock;

extern sem_t emptyReaderBuffer;
extern sem_t fullReaderBuffer;

extern pthread_cond_t readerCond;
extern pthread_cond_t analyzerCond;


#endif //CPU_USAGE_TRACKER_ANALYZER_H
