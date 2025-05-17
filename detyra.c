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