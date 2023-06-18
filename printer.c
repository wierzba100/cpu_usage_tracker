//
// Created by filip on 18.06.23.
//
#include <stdio.h>
#include <unistd.h>
#include "printer.h"
#include "reader.h"

void *printer(void *CPUs_DataIn)
{
    CPUs_Data* CPUMy_Data = (CPU_Data *)CPUs_DataIn;
    long number_of_processors = sysconf(_SC_NPROCESSORS_ONLN);
    while(1)
    {
        printf("Dane:\n");
        for(int i=0;i<number_of_processors;i++) {
            printf("CPU %d: %f %% \n",i,CPUMy_Data->usage[i]);
        }
        usleep(100000);
    }


}