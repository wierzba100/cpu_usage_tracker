//
// Created by filip on 18.06.23.
//

#ifndef GPU_USAGE_TRACKER_ANALYZER_H
#define GPU_USAGE_TRACKER_ANALYZER_H

#include "global_variables.h"

double proc_usage(CPU_Data, CPU_Data);

void *analyzer(void *);

extern pthread_mutex_t lock;
extern pthread_cond_t readerCond;
extern pthread_cond_t analyzerCond;

#endif //GPU_USAGE_TRACKER_ANALYZER_H
