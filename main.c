#include "global_variables.h"
#include "reader.h"
#include "analyzer.h"
#include "printer.h"
#include "watchdog.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t watchdog_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t readerCond = PTHREAD_COND_INITIALIZER;
pthread_cond_t analyzerCond = PTHREAD_COND_INITIALIZER;
bool Threads_Table[NR_OF_THREADS];

int main()
{
    CPUs_Data CPUs_Data;

    pthread_t thread0, thread1, thread2, thread3;

    pthread_create(&thread0, NULL, reader, (void*) &CPUs_Data);
    pthread_create(&thread1, NULL, analyzer, (void*) &CPUs_Data);
    pthread_create(&thread2, NULL, printer, (void*) &CPUs_Data);
    pthread_create(&thread3, NULL, watchdog, NULL);

    pthread_join(thread0, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);


    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&readerCond);
    pthread_cond_destroy(&analyzerCond);
    return 0;
}
