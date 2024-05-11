#include "../hdr/global_variables.h"
#include "../hdr/reader.h"
#include "../hdr/analyzer.h"
#include "../hdr/printer.h"
#include "../hdr/watchdog.h"
#include "../hdr/sigterm.h"
#include "../hdr/logger.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t watchdog_mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t emptyReaderBuffer;
sem_t fullReaderBuffer;
pthread_cond_t readerCond = PTHREAD_COND_INITIALIZER;
pthread_cond_t analyzerCond = PTHREAD_COND_INITIALIZER;
pthread_cond_t watchdogCond = PTHREAD_COND_INITIALIZER;

int Threads_Table[NR_OF_THREADS];
volatile sig_atomic_t done = 0;
long number_of_processors;

#define SECONDS_TO_RUN 5

void *terminate_after_N_sec(void* SecondsIn)
{
    int* Seconds = (int *) SecondsIn;
    sleep(*Seconds);
    term(0);
    return NULL;
}

int main()
{
    number_of_processors = sysconf(_SC_NPROCESSORS_ONLN);
    int nr_of_seconds = SECONDS_TO_RUN;
    int* ptr_nr_of_seconds = &nr_of_seconds;

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

    pthread_t thread0, thread1, thread2, thread3, thread4, thread5;

    SIGTERM_init();

    pthread_create(&thread0, NULL, reader, (void*) ptrMyAnalyzerData);
    pthread_create(&thread1, NULL, analyzer, (void*) ptrMyAnalyzerData);
    pthread_create(&thread2, NULL, printer, (void*) ptrMyAnalyzerData);
    pthread_create(&thread3, NULL, watchdog, NULL);
    pthread_create(&thread4, NULL, logger, (void*) ptrMyAnalyzerData);
    pthread_create(&thread5, NULL, terminate_after_N_sec, (void*) ptr_nr_of_seconds);

    pthread_join(thread0, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    pthread_join(thread5, NULL);

    pthread_mutex_destroy(&lock);
    pthread_mutex_destroy(&watchdog_mutex);
    pthread_cond_destroy(&watchdogCond);
    pthread_cond_destroy(&analyzerCond);
    pthread_cond_destroy(&readerCond);

    sem_destroy(&emptyReaderBuffer);
    sem_destroy(&fullReaderBuffer);

    for(int i=0;i<BUFFER_SIZE;i++)
    {
        free(ReaderData[i]);
        free(PrinterData[i]);
    }

    printf("Program closed\n");
    return 0;
}
