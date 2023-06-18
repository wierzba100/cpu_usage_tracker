//
// Created by filip on 18.06.23.
//
#include "printer.h"

void *printer(void *CPUs_DataIn)
{
    CPUs_Data* CPUMy_Data = (CPUs_Data *) CPUs_DataIn;
    long number_of_processors = sysconf(_SC_NPROCESSORS_ONLN);
    while(1)
    {
        pthread_mutex_lock(&lock);
        pthread_cond_wait(&analyzerCond, &lock);
        printf("Dane:\n");
        for(int i=0;i<number_of_processors;i++) {
            printf("CPU %d: %f %% \n",i,CPUMy_Data->usage[i]);
        }
        pthread_mutex_unlock(&lock);
        sleep(1);
    }

}