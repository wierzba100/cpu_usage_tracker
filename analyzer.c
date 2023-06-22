//
// Created by filip on 18.06.23.
//

#include "analyzer.h"

void processor_usage(CPU_Data* Current_Data, CPU_Data* Previous_Data, double* usageIn)
{
    unsigned long previousTotal = Previous_Data->user + Previous_Data->nice +
                              Previous_Data->system + Previous_Data->idle +
                              Previous_Data->iowait + Previous_Data->irq +
                              Previous_Data->softirq + Previous_Data->steal;

    unsigned long currentTotal = Current_Data->user + Current_Data->nice +
                                 Current_Data->system + Current_Data->idle +
                                 Current_Data->iowait + Current_Data->irq +
                                 Current_Data->softirq + Current_Data->steal;

    unsigned long total = currentTotal - previousTotal;
    unsigned long idle = Current_Data->idle - Previous_Data->idle;

    double usage = (double)(total - idle) / (double)total * 100;

    *usageIn = usage;
}




void *analyzer(void *CPUs_DataIn)
{
    AnalyzerData* CPUMy_Data = (AnalyzerData *) CPUs_DataIn;
    while(!done)
    {
        pthread_mutex_lock(&lock);
        thread_is_working(1);
        pthread_cond_wait(&readerCond, &lock);
        for(int i=0;i<number_of_processors;i++)
        {
            processor_usage(&CPUMy_Data->ReaderData[0][i], &CPUMy_Data->ReaderData[1][i], &CPUMy_Data->PrinterData[0][i]);
        }
        pthread_mutex_unlock(&lock);
        pthread_cond_signal(&analyzerCond);
    }
    return NULL;
}