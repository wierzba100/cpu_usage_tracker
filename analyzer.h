//
// Created by filip on 18.06.23.
//

#ifndef CPU_USAGE_TRACKER_ANALYZER_H
#define CPU_USAGE_TRACKER_ANALYZER_H

#include "global_variables.h"

double processor_usage(CPU_Data*, CPU_Data*);

void *analyzer(void *);

extern pthread_mutex_t lock;
extern pthread_cond_t readerCond;
extern pthread_cond_t analyzerCond;

#endif //CPU_USAGE_TRACKER_ANALYZER_H
