//
// Created by filip on 18.06.23.
//

#ifndef GPU_USAGE_TRACKER_GLOBAL_VARIABLES_H
#define GPU_USAGE_TRACKER_GLOBAL_VARIABLES_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>

#define MAX_NR_OF_PROCESSORS 12
#define WATCHDOG_TIMEOUT 2
#define NR_OF_THREADS 4

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

extern long number_of_processors;

extern void thread_is_working(int Thread_nr);

extern volatile sig_atomic_t done;
extern void term(int);


#endif //GPU_USAGE_TRACKER_GLOBAL_VARIABLES_H
