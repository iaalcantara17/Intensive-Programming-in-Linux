#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    long threadId;
    long numThreads;
    long numTerms;
    double *partialSums;
} ThreadData;

void *computePi(void *arg)
{
    ThreadData *td = (ThreadData *)arg;
    long id = td->threadId;
    long nThreads = td->numThreads;
    long nTerms = td->numTerms;
    long chunk = nTerms / nThreads;
    long start = id * chunk;
    long end = (id == nThreads - 1) ? nTerms : start + chunk;
    double sum = 0.0;
    double dx = 1.0 / (double)nTerms;
    for (long i = start; i < end; i++) {
        double x = (i + 0.5) * dx;
        sum += 1.0 / (1.0 + x * x);
    }
    td->partialSums[id] = sum;
    return NULL;
}

int main(int argc, char *argv[])
{
    long numTerms;
    int numThreads;
    if (argc != 3)
        return 1;
    numTerms = atol(argv[1]);
    numThreads = atoi(argv[2]);
    pthread_t *threads = malloc(numThreads * sizeof(pthread_t));
    double *partialSums = malloc(numThreads * sizeof(double));
    ThreadData *td = malloc(numThreads * sizeof(ThreadData));
    for (int t = 0; t < numThreads; t++) {
        td[t].threadId = t;
        td[t].numThreads = numThreads;
        td[t].numTerms = numTerms;
        td[t].partialSums = partialSums;
        pthread_create(&threads[t], NULL, computePi, &td[t]);
    }
    for (int t = 0; t < numThreads; t++)
        pthread_join(threads[t], NULL);
    double total = 0.0;
    for (int t = 0; t < numThreads; t++)
        total += partialSums[t];
    double pi = 4.0 * total / numTerms;
    printf("%.15f\n", pi);
    free(threads);
    free(partialSums);
    free(td);
    return 0;
}

