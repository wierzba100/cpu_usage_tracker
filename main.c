#include "global_variables.h"
#include "reader.h"
#include "analyzer.h"
#include "printer.h"
#include "watchdog.h"
#include "sigterm.h"
#include "logger.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t watchdog_mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t emptyReaderBuffer;
sem_t fullReaderBuffer;
sem_t emptyUsageBuffer;
sem_t fullUsageBuffer;
pthread_cond_t readerCond = PTHREAD_COND_INITIALIZER;
pthread_cond_t analyzerCond = PTHREAD_COND_INITIALIZER;
pthread_cond_t watchdogCond = PTHREAD_COND_INITIALIZER;

int Threads_Table[NR_OF_THREADS];
volatile sig_atomic_t done = 0;
long number_of_processors;


int main()
{
    number_of_processors = sysconf(_SC_NPROCESSORS_ONLN);

    CPU_Data* ReaderData[BUFFER_SIZE];
    double* PrinterData[BUFFER_SIZE];

    AnalyzerData MyAnalyzerData = {ReaderData, PrinterData};
    const AnalyzerData* ptrMyAnalyzerData = &MyAnalyzerData;

    for(int i=0;i<BUFFER_SIZE;i++)
    {
        ReaderData[i] = calloc(number_of_processors, sizeof(CPU_Data));
        PrinterData[i] = calloc(number_of_processors, sizeof(double));
    }

    sem_init(&emptyReaderBuffer, 0, BUFFER_SIZE);
    sem_init(&fullReaderBuffer, 0, 0);
    sem_init(&emptyUsageBuffer, 0, BUFFER_SIZE);
    sem_init(&fullUsageBuffer, 0, 0);

    pthread_t thread0, thread1, thread2, thread3, thread4;

    SIGTERM_init();

    pthread_create(&thread0, NULL, reader, (void*) ptrMyAnalyzerData);
    pthread_create(&thread1, NULL, analyzer, (void*) ptrMyAnalyzerData);
    pthread_create(&thread2, NULL, printer, (void*) ptrMyAnalyzerData);
    pthread_create(&thread3, NULL, watchdog, NULL);
    pthread_create(&thread4, NULL, logger, (void*) ptrMyAnalyzerData);

    pthread_join(thread0, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);

    pthread_mutex_destroy(&lock);
    pthread_mutex_destroy(&watchdog_mutex);
    pthread_cond_destroy(&watchdogCond);
    pthread_cond_destroy(&analyzerCond);
    pthread_cond_destroy(&readerCond);

    sem_destroy(&emptyReaderBuffer);
    sem_destroy(&fullReaderBuffer);
    sem_destroy(&emptyUsageBuffer);
    sem_destroy(&fullUsageBuffer);

    for(int i=0;i<BUFFER_SIZE;i++)
    {
        free(ReaderData[i]);
        free(PrinterData[i]);
    }

    printf("Program closed\n");
    return 0;
}
