#ifndef CPU_USAGE_TRACKER_READER_H
#define CPU_USAGE_TRACKER_READER_H

#include "global_variables.h"

void *readCPUData(CPU_Data*);
void *reader(void*);

extern pthread_mutex_t lock;

extern pthread_cond_t readerCond;

extern sem_t emptyReaderBuffer;
extern sem_t fullReaderBuffer;

#endif //CPU_USAGE_TRACKER_READER_H
