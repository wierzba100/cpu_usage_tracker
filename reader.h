//
// Created by filip on 17.06.23.
//

#ifndef CPU_USAGE_TRACKER_READER_H
#define CPU_USAGE_TRACKER_READER_H

#include "global_variables.h"

void *readCPUdata(CPU_Data*, long);
void *reader(void*);

extern pthread_mutex_t lock;
extern pthread_cond_t readerCond;

#endif //CPU_USAGE_TRACKER_READER_H
