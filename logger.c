//
// Created by filip on 18.06.23.
//

#include "logger.h"

void *logger(void *CPUs_DataIn)
{
    CPUs_Data* CPUMy_Data = (CPUs_Data *) CPUs_DataIn;
    FILE *fp;
    fp = fopen("../logger_data.log", "w");
    if (fp == NULL) {
        printf("Can't open 'logger_data.log'. Whether the file exists?\n");
        term(0);
    }else
    {
        fprintf (fp, "Logger Start\n");
        while(!done)
        {
            thread_is_working(3);
            fprintf (fp, "Processors Usage:\n");
            pthread_mutex_lock(&lock);
            for(int i=0;i<number_of_processors;i++) {
                fprintf (fp, "CPU_NR: %d Usage: %f %%\n",i, CPUMy_Data->usage[i]);
            }
            pthread_mutex_unlock(&lock);
            sleep(1);
        }
        fprintf (fp, "Logger Stop\n");
        fclose(fp);
    }

}
