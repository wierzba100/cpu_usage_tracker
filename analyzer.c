//
// Created by filip on 18.06.23.
//

#include <unistd.h>
#include "analyzer.h"

unsigned long proc_usage(CPU_Data Current_Data, CPU_Data Previous_Data)
{
    unsigned long prevIdle = Previous_Data.idle + Previous_Data.iowait;
    unsigned long idle = Current_Data.idle + Current_Data.iowait;

    unsigned long prevNonIdle = Previous_Data.user + Previous_Data.nice + Previous_Data.system + Previous_Data.irq +
            Previous_Data.softirq + Previous_Data.steal;
    unsigned long nonIdle = Current_Data.user + Current_Data.nice + Current_Data.system +
            Current_Data.irq + Current_Data.softirq + Current_Data.steal;

    unsigned long prevTotal = prevIdle + prevNonIdle;
    unsigned long total = idle + nonIdle;

    total = total - prevTotal;
    idle = idle - prevIdle;

    if(total != 0)
    {
        unsigned long usage = (total - idle) * 100 / total;
        return usage;
    }

    return 0;
}


void *analyzer(void *CPUs_DataIn)
{
    CPUs_Data* CPUMy_Data = (CPU_Data *)CPUs_DataIn;
    long number_of_processors = sysconf(_SC_NPROCESSORS_ONLN);
    while(1)
    {
        for(int i=0;i<number_of_processors;i++) {
            CPUMy_Data->usage[i] = proc_usage(CPUMy_Data->CurrentCPUs_Data[i], CPUMy_Data->PreviousCPUs_Data[i]);
        }

    }

}