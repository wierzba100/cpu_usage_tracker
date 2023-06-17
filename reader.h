//
// Created by filip on 17.06.23.
//

#ifndef GPU_USAGE_TRACKER_READER_H
#define GPU_USAGE_TRACKER_READER_H

typedef struct {
    unsigned long user;
    unsigned long nice;
    unsigned long system;
    unsigned long idle;
    unsigned long iowait;
    unsigned long irq;
    unsigned long softirq;
    unsigned long steal;
    unsigned long guest;
    unsigned long guest_nice;
} CPU_Data;


void *readCPUdata(void*);

#endif //GPU_USAGE_TRACKER_READER_H
