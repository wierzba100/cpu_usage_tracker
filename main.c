#include <stdio.h>
#include <pthread.h>
#include "reader.c"

#define MAX_NR_OF_PROCESSORS 12


int main()
{
    CPU_Data CPUs_Data[MAX_NR_OF_PROCESSORS];

    pthread_t thread1;

    pthread_create(&thread1, NULL, readCPUdata, (void*) &CPUs_Data);
    while(1)
    {
        int a=1, b=2, suma;
        suma = a + b;
    }
    return 0;
}
