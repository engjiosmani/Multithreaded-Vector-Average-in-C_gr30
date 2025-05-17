#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define VECTOR_SIZE 100
#define NUM_THREADS 4

int vector[VECTOR_SIZE];
double partial_sums[NUM_THREADS];
int elements_per_thread;

typedef struct {
int thread_id;
int start_index;
int end_index;
} ThreadData;

void* calculate_partial_sum(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    int start = data->start_index;
    int end = data->end_index;
    double sum = 0;

    for (int i = start; i < end; i++) {
        sum += vector[i];
    }

    partial_sums[data->thread_id] = sum;

    printf("Thread %d: start = %d, end = %d, sum = %.2f\n",
           data->thread_id, start, end, sum);

    pthread_exit(NULL);
}