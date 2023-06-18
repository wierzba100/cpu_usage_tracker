#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "reader.h"

void *readCPUdata(CPU_Data *CPUs_Data, long nr_of_proc)
{
    FILE *fp;
    fp = fopen("/proc/stat", "r");
    if (fp == NULL) {
        printf("nie ma pliku");
    } else {
        char buffer[256];
        CPU_Data CPU;
        for(int i = 0;i<nr_of_proc;i++) {
            if ( (fgets(buffer, sizeof(buffer), fp) != NULL) ||  (strncmp(buffer, "cpu", 3) == 0))
            {
                sscanf(buffer + 4, "%lu %lu %lu %lu %lu %lu %lu %lu %lu %lu",
                       &CPU.user, &CPU.nice, &CPU.system, &CPU.idle, &CPU.iowait,
                       &CPU.irq, &CPU.softirq, &CPU.steal, &CPU.guest, &CPU.guest_nice);
                CPUs_Data[i] = CPU;
            } else {
                fclose(fp);
            }
        }
        fclose(fp);
    }
}


void *reader(void *CPUs_DataIn)
{
    CPUs_Data* CPUMy_Data = (CPU_Data *)CPUs_DataIn;
    long number_of_processors = sysconf(_SC_NPROCESSORS_ONLN);
    CPU_Data CPUs_Stats[MAX_NR_OF_PROCESSORS];
    while(1)
    {
        readCPUdata(&CPUs_Stats, number_of_processors);
        for(int i=0;i<number_of_processors;i++) {
            CPUMy_Data->PreviousCPUs_Data[i] = CPUMy_Data->CurrentCPUs_Data[i];
            CPUMy_Data->CurrentCPUs_Data[i] = CPUs_Stats[i];
        }
        usleep(100000);
    }
}

