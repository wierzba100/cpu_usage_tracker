#include <stdio.h>
#include <string.h>
#include "reader.c"

CPU_Data CPUs_Data[MAX_NR_OF_PROCESSORS];

int main()
{
    while(1)
    {
        readCPUdata(&CPUs_Data);
    }
    return 0;
}
