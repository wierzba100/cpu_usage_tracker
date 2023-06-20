//
// Created by filip on 18.06.23.
//

#ifndef CPU_USAGE_TRACKER_PRINTER_H
#define CPU_USAGE_TRACKER_PRINTER_H

#include "global_variables.h"

void *printer(void*);

extern pthread_mutex_t lock;
extern pthread_cond_t analyzerCond;


#endif //CPU_USAGE_TRACKER_PRINTER_H
