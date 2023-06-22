//
// Created by filip on 18.06.23.
//
#include "printer.h"

void *printer(void *CPU_UsageIn)
{
    double** CPUMy_Data = (double **) CPU_UsageIn;
    while(!done)
    {
        pthread_mutex_lock(&lock);
        thread_is_working(2);
        pthread_cond_wait(&analyzerCond, &lock);
        printf("Processor usage:\n");
        for(int i=0;i<number_of_processors;i++) {
            printf("CPU %d: %f %% \n",i,CPUMy_Data[0][i]);
        }
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    return NULL;
}
