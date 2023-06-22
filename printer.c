//
// Created by filip on 18.06.23.
//
#include "printer.h"

void *printer(void *CPUs_DataIn)
{
    AnalyzerData* CPUMy_Data = (AnalyzerData *) CPUs_DataIn;
    while(!done)
    {
        pthread_mutex_lock(&lock);
        thread_is_working(2);
        pthread_cond_wait(&analyzerCond, &lock);
        printf("Processor usage:\n");
        for(int i=0;i<number_of_processors;i++) {
            printf("CPU %d: %f %% \n",i,CPUMy_Data->PrinterData[0][i]);
        }
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    return NULL;
}
