#include "global_variables.h"
#include "reader.h"
#include "analyzer.h"
#include "printer.h"
#include "watchdog.h"
#include "sigterm.h"
#include "logger.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t watchdog_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t readerCond = PTHREAD_COND_INITIALIZER;
pthread_cond_t analyzerCond = PTHREAD_COND_INITIALIZER;
pthread_cond_t watchdogCond = PTHREAD_COND_INITIALIZER;

int Threads_Table[NR_OF_THREADS];
volatile sig_atomic_t done = 0;
long number_of_processors;

int main()
{
    CPUs_Data CPUs_Data={0};
    number_of_processors = sysconf(_SC_NPROCESSORS_ONLN);

    pthread_t thread0, thread1, thread2, thread3, thread4;

    SIGTERM_init();

    pthread_create(&thread0, NULL, reader, (void*) &CPUs_Data);
    pthread_create(&thread1, NULL, analyzer, (void*) &CPUs_Data);
    pthread_create(&thread2, NULL, printer, (void*) &CPUs_Data);
    pthread_create(&thread3, NULL, watchdog, NULL);
    pthread_create(&thread4, NULL, logger, (void*) &CPUs_Data);

    pthread_join(thread0, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);

    pthread_mutex_destroy(&lock);
    pthread_mutex_destroy(&watchdog_mutex);
    pthread_cond_destroy(&readerCond);
    pthread_cond_destroy(&analyzerCond);
    pthread_cond_destroy(&watchdogCond);

    printf("Program closed\n");
    return 0;
}
