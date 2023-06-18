//
// Created by filip on 17.06.23.
//

#ifndef GPU_USAGE_TRACKER_READER_H
#define GPU_USAGE_TRACKER_READER_H

#include "global_variables.h"

void *readCPUdata(CPU_Data*, long);
void *reader(void*);

extern pthread_mutex_t lock;
extern pthread_cond_t readerCond;

#endif //GPU_USAGE_TRACKER_READER_H
