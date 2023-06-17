#include <stdio.h>
#include <string.h>
#include "reader.h"

void readCPUdata(CPU_Data* CPUs_Data)
{
    FILE *fp;
    fp = fopen("/proc/stat", "r");
    if (fp == NULL)
    {
        printf("nie ma pliku");
    }else
    {
        char buffer[256];
        int i=0;
        while (fgets(buffer, sizeof(buffer), fp))
        {
            if (strncmp(buffer, "cpu", 3) == 0)
            {
                CPU_Data CPU;
                sscanf(buffer + 4, "%lu %lu %lu %lu %lu %lu %lu %lu %lu %lu",
                       &CPU.user, &CPU.nice, &CPU.system, &CPU.idle, &CPU.iowait,
                       &CPU.irq, &CPU.softirq, &CPU.steal, &CPU.guest, &CPU.guest_nice);
                CPUs_Data[i] = CPU;
                i++;
            }else
            {
                fclose(fp);
            }
        }
    }
}