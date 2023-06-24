//
// Created by filip on 18.06.23.
//

#include "analyzer.h"

void processor_usage(CPU_Data* Current_Data, CPU_Data* Previous_Data, double* usageIn)
{
    for(int i=0;i<number_of_processors;i++) {
        unsigned long previousTotal = Previous_Data[i].user + Previous_Data[i].nice +
                                      Previous_Data[i].system + Previous_Data[i].idle +
                                      Previous_Data[i].iowait + Previous_Data[i].irq +
                                      Previous_Data[i].softirq + Previous_Data[i].steal;

        unsigned long currentTotal = Current_Data[i].user + Current_Data[i].nice +
                                     Current_Data[i].system + Current_Data[i].idle +
                                     Current_Data[i].iowait + Current_Data[i].irq +
                                     Current_Data[i].softirq + Current_Data[i].steal;

        unsigned long total = currentTotal - previousTotal;
        unsigned long idle = Current_Data[i].idle - Previous_Data[i].idle;

        double usage = (double) (total - idle) / (double) total * 100;

        usageIn[i] = usage;
    }
}


void *analyzer(void *CPUs_DataIn)
{
    AnalyzerData* CPUMy_Data = (AnalyzerData *) CPUs_DataIn;
    unsigned int bufferReaderIndex=0;
    while(!done)
    {
        thread_is_working(1);
        sem_wait(&fullReaderBuffer);
        pthread_mutex_lock(&lock);
        pthread_cond_wait(&readerCond, &lock);
        processor_usage(CPUMy_Data->ReaderData[(bufferReaderIndex+1) % BUFFER_SIZE], CPUMy_Data->ReaderData[bufferReaderIndex % BUFFER_SIZE],
                        CPUMy_Data->PrinterData[bufferReaderIndex % BUFFER_SIZE]);
        pthread_mutex_unlock(&lock);
        sem_post(&emptyReaderBuffer);
        bufferReaderIndex++;
        pthread_cond_signal(&analyzerCond);
    }
    return NULL;
}