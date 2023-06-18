//
// Created by filip on 18.06.23.
//

#ifndef GPU_USAGE_TRACKER_PRINTER_H
#define GPU_USAGE_TRACKER_PRINTER_H

#include "global_variables.h"

void *printer(void*);

extern pthread_mutex_t lock;
extern pthread_cond_t analyzerCond;


#endif //GPU_USAGE_TRACKER_PRINTER_H
