//
// Created by filip on 18.06.23.
//

#include "analyzer.h"

double proc_usage(CPU_Data Current_Data, CPU_Data Previous_Data)
{
    unsigned long prevTotal = Previous_Data.user + Previous_Data.nice +
                              Previous_Data.system + Previous_Data.idle +
                              Previous_Data.iowait + Previous_Data.irq +
                              Previous_Data.softirq + Previous_Data.steal;

    unsigned long currentTotal = Current_Data.user + Current_Data.nice +
                                 Current_Data.system + Current_Data.idle +
                                 Current_Data.iowait + Current_Data.irq +
                                 Current_Data.softirq + Current_Data.steal;

    unsigned long total = currentTotal - prevTotal;
    unsigned long idle = Current_Data.idle - Previous_Data.idle;

    double usage = (double)(total - idle) / (double)total * 100;

    return usage;
}


void *analyzer(void *CPUs_DataIn)
{
    CPUs_Data* CPUMy_Data = (CPUs_Data *) CPUs_DataIn;
    long number_of_processors = sysconf(_SC_NPROCESSORS_ONLN);
    while(1)
    {
        pthread_mutex_lock(&lock);
        thread_is_working(1);
        pthread_cond_wait(&readerCond, &lock);
        for(int i=0;i<number_of_processors;i++) {
            CPUMy_Data->usage[i] = proc_usage(CPUMy_Data->CurrentCPUs_Data[i], CPUMy_Data->PreviousCPUs_Data[i]);
        }
        pthread_mutex_unlock(&lock);
        pthread_cond_signal(&analyzerCond);
    }
}