/* benford_par_global_single_mutex.c
 *
 * Parallel Benford counter:
 * Version (i): Global counter array protected by a SINGLE mutex.
 *
 * Compile with:
 * gcc -o benford_par_global_single_mutex \
 *  my_timing.c benford_par_global_single_mutex.c benford_helper.c \
 *  -lm -lpthread
 *
 * Run with:
 * ./benford_par_global_single_mutex
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "my_timing.h"

// Bring in global variables + functions from benford_sequential.c
extern int N;
extern double *data;
int loadData(char *filename);
int leadingDigit(double n);

#define NUM_THREADS 8

// global counter array + single mutex
int global_counts[10];
pthread_mutex_t lock;

// Struct to hold thread work info
typedef struct {
    int tid;
    int start;
    int end;
} ThreadInfo;

// Worker thread
void *worker(void *arg) {
    ThreadInfo *ti = (ThreadInfo *)arg;

    for (int i = ti->start; i < ti->end; i++) {
        int d = leadingDigit(data[i]);

        // Protect shared counter updates
        pthread_mutex_lock(&lock);
        global_counts[d]++;
        pthread_mutex_unlock(&lock);
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    double t1, t2;

    // Load data exactly as sequential version does
    if (!loadData("medium.bin")) {
        printf("Error loading data.\n");
        return -1;
    }

    // Initialize global counters and mutex
    for (int i = 0; i < 10; i++)
        global_counts[i] = 0;

    pthread_mutex_init(&lock, NULL);

    // Start timing
    t1 = get_time_sec();

    pthread_t threads[NUM_THREADS];
    ThreadInfo ti[NUM_THREADS];

    // Work division
    int base = N / NUM_THREADS;
    int extra = N % NUM_THREADS;

    int index = 0;
    for (int t = 0; t < NUM_THREADS; t++) {
        ti[t].tid = t;
        ti[t].start = index;

        int size = base;
        if (t == NUM_THREADS - 1)
            size += extra; // last thread gets remainder

        ti[t].end = index + size;
        index += size;

        pthread_create(&threads[t], NULL, worker, &ti[t]);
    }

    // Join threads
    for (int t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    t2 = get_time_sec();

    // Print results (digits 1 through 9) just like sequential version
    for (int d = 1; d < 10; d++) {
        printf("There are %d %d's\n", global_counts[d], d);
    }

    printf("It took %f seconds for the whole thing to run\n", t2 - t1);

    // Cleanup
    pthread_mutex_destroy(&lock);
    free(data);

    return 0;
}
