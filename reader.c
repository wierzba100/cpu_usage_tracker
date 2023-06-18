#include "reader.h"
#include <string.h>

void *readCPUdata(CPU_Data *CPUs_Data, long nr_of_proc)
{
    FILE *fp;
    fp = fopen("/proc/stat", "r");
    if (fp == NULL) {
        printf("nie ma pliku");
    } else {
        char buffer[256];
        for(int i = 0;i<nr_of_proc;i++) {
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
}


void *reader(void *CPUs_DataIn)
{
    CPUs_Data* CPUMy_Data = (CPUs_Data *) CPUs_DataIn;
    long number_of_processors = sysconf(_SC_NPROCESSORS_ONLN);
    CPU_Data CPUs_Stats[MAX_NR_OF_PROCESSORS];
    while(1)
    {
        pthread_mutex_lock(&lock);
        thread_is_working(0);
        readCPUdata(CPUs_Stats, number_of_processors);
        for(int i=0;i<number_of_processors;i++) {
            CPUMy_Data->PreviousCPUs_Data[i] = CPUMy_Data->CurrentCPUs_Data[i];
            CPUMy_Data->CurrentCPUs_Data[i] = CPUs_Stats[i];
        }
        pthread_mutex_unlock(&lock);
        pthread_cond_signal(&readerCond);
        usleep(20000);
    }
}

