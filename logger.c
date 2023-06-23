//
// Created by filip on 18.06.23.
//

#include <time.h>
#include "logger.h"

void *logger(void *CPUs_DataIn)
{
    AnalyzerData* CPUMy_Data = (AnalyzerData *) CPUs_DataIn;
    time_t rawtime;
    struct tm * timeinfo;
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
            sleep(1);
            time ( &rawtime );
            timeinfo = localtime ( &rawtime );
            fprintf (fp, "\nTime and date: %s", asctime (timeinfo) );
            fprintf (fp, "Processor Usage:\n");
            pthread_mutex_lock(&lock);
            //pthread_cond_wait(&analyzerCond, &lock);
            for(int i=0;i<number_of_processors;i++) {
                fprintf (fp, "CPU_NR: %d Usage: %f %%\n",i, CPUMy_Data->PrinterData[0][i]);
            }
            pthread_mutex_unlock(&lock);
            fprintf (fp, "Watchdog Table:\n");
            pthread_mutex_lock(&watchdog_mutex);
            pthread_cond_wait(&watchdogCond, &watchdog_mutex);
            for(int i=0;i<NR_OF_THREADS;i++) {
                fprintf(fp, "Status watku %d: %d\n", i, Threads_Table[i]);
            }
            pthread_mutex_unlock(&watchdog_mutex);
            fprintf (fp, "Status of SIGTERM: %d\n", done);

        }
        fprintf (fp, "Logger Stop\n");
        fclose(fp);
    }
    return NULL;
}
