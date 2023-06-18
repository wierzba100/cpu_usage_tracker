//
// Created by filip on 18.06.23.
//

#ifndef GPU_USAGE_TRACKER_GLOBAL_VARIABLES_H
#define GPU_USAGE_TRACKER_GLOBAL_VARIABLES_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_NR_OF_PROCESSORS 12

typedef struct{
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

typedef struct{
    CPU_Data CurrentCPUs_Data[MAX_NR_OF_PROCESSORS];
    CPU_Data PreviousCPUs_Data[MAX_NR_OF_PROCESSORS];
    double usage[MAX_NR_OF_PROCESSORS];
}CPUs_Data;

#endif //GPU_USAGE_TRACKER_GLOBAL_VARIABLES_H
