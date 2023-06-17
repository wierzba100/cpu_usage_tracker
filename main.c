#include <stdio.h>
#include <pthread.h>
#include "reader.c"



int main()
{
    CPUs_Data CPUs_Data;

    pthread_t thread0, thread1;

    pthread_create(&thread0, NULL, reader, (void*) &CPUs_Data);
    while(1)
    {
        int a=1, b=2, suma;
        suma = a + b;
    }
    return 0;
}
