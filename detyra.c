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

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    elements_per_thread = VECTOR_SIZE / NUM_THREADS;

    for (int i = 0; i < VECTOR_SIZE; i++) {
        vector[i] = i + 1;
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].thread_id = i;
        thread_data[i].start_index = i * elements_per_thread;
        thread_data[i].end_index = (i == NUM_THREADS - 1) ?
            VECTOR_SIZE : (i + 1) * elements_per_thread;

        pthread_create(&threads[i], NULL, calculate_partial_sum, (void*)&thread_data[i]);
    }
}
