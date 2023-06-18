#include <stdio.h>
#include <pthread.h>
#include "reader.c"
#include "analyzer.h"
#include "printer.h"



int main()
{
    CPUs_Data CPUs_Data;

    pthread_t thread0, thread1, thread2;

    pthread_create(&thread0, NULL, reader, (void*) &CPUs_Data);
    pthread_create(&thread1, NULL, analyzer, (void*) &CPUs_Data);
    pthread_create(&thread2, NULL, printer, (void*) &CPUs_Data);
    while(1);
    return 0;
}
