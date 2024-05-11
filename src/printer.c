#include "../hdr/printer.h"

void *printer(void *CPUs_DataIn)
{
    AnalyzerData* CPUMy_Data = (AnalyzerData *) CPUs_DataIn;
    unsigned int bufferUsageIndex=0;
    while(!done)
    {
        thread_is_working(2);
        pthread_mutex_lock(&lock);
        pthread_cond_wait(&analyzerCond, &lock);
        printf("Processor usage:\n");
        for(int i=0;i<number_of_processors;i++) {
            printf("CPU %d: %f %% \n",i,CPUMy_Data->PrinterData[bufferUsageIndex % BUFFER_SIZE][i]);
        }
        pthread_mutex_unlock(&lock);
        bufferUsageIndex++;
        sleep(1);
    }
    return NULL;
}
