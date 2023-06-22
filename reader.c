#include "reader.h"
#include <string.h>

void *readCPUdata(CPU_Data* CPUs_Data)
{
    FILE *fp;
    fp = fopen("/proc/stat", "r");
    if (fp == NULL) {
        printf("Can't open '/proc/stat' file. ERROR");
        term(0);
    } else {
        char buffer[256];
        for(int i = 0;i<number_of_processors;i++) {
            if ( (fgets(buffer, sizeof(buffer), fp) != NULL) ||  (strncmp(buffer, "cpu", 3) == 0))
            {
                sscanf(buffer + 4, "%lu %lu %lu %lu %lu %lu %lu %lu %lu %lu",
                       &CPUs_Data[i].user, &CPUs_Data[i].nice,&CPUs_Data[i].system,&CPUs_Data[i].idle,
                       &CPUs_Data[i].iowait,&CPUs_Data[i].irq, &CPUs_Data[i].softirq, &CPUs_Data[i].steal,
                       &CPUs_Data[i].guest, &CPUs_Data[i].guest_nice);
            } else {
                fclose(fp);
            }
        }
        fclose(fp);
    }
    return NULL;
}


void *reader(void *CPUs_DataIn)
{
    CPU_Data** CPUMy_Data = (CPU_Data **) CPUs_DataIn;
    while(!done)
    {
        usleep(500000);
        pthread_mutex_lock(&lock);
        thread_is_working(0);
        for(int i=0;i<number_of_processors;i++)
        {
            memcpy(CPUMy_Data[i+1], CPUMy_Data[0], number_of_processors * sizeof(CPU_Data));
        }
        readCPUdata(CPUMy_Data[0]);
        pthread_mutex_unlock(&lock);
        pthread_cond_signal(&readerCond);
    }
    return NULL;
}

