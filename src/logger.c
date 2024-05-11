#include <time.h>
#include "../hdr/logger.h"

void *logger(void *CPUs_DataIn)
{
    AnalyzerData* CPUMy_Data = (AnalyzerData *) CPUs_DataIn;
    int valueToPrint;
    unsigned int bufferUsageIndex=0;
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
            pthread_cond_wait(&analyzerCond, &lock);
            for(int i=0;i<number_of_processors;i++) {
                fprintf (fp, "CPU_NR: %d Usage: %f %%\n",i, CPUMy_Data->PrinterData[bufferUsageIndex % BUFFER_SIZE][i]);
            }
            sem_getvalue(&emptyReaderBuffer, &valueToPrint);
            fprintf(fp, "emptyReaderBuffer: %d\n", valueToPrint);
            sem_getvalue(&fullReaderBuffer, &valueToPrint);
            fprintf(fp, "fullReaderBuffer: %d\n", valueToPrint);
            pthread_mutex_unlock(&lock);
            bufferUsageIndex++;
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
