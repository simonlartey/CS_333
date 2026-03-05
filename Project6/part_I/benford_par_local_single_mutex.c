/* benford_par_local_single_mutex.c
 *
 * Parallel Benford counter:
 * Version (iii): Local counter per thread.
 * Each thread counts independently with NO mutexes,
 * then uses ONE mutex to merge into the global array.
 *
 * Compile with:
 * gcc -o benford_par_local_single_mutex \
 *     my_timing.c benford_par_local_single_mutex.c benford_helper.c \
 *     -lm -lpthread
 * 
 * Run with:
 * ./benford_par_local_single_mutex
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "my_timing.h"

// External globals from helper
extern int N;
extern double *data;
int loadData(char *filename);
int leadingDigit(double n);

#define NUM_THREADS 8

// Global result array
int global_counts[10];

// Single mutex for merging
pthread_mutex_t merge_lock;

// Thread info struct
typedef struct {
    int tid;
    int start;
    int end;
} ThreadInfo;

void *worker(void *arg) {
    ThreadInfo *ti = (ThreadInfo *)arg;

    // Local counter for this thread (NO LOCKING needed)
    int local_counts[10] = {0};

    // Count in this thread's chunk
    for (int i = ti->start; i < ti->end; i++) {
        int d = leadingDigit(data[i]);
        local_counts[d]++;
    }

    // Merge into global_counts using ONE mutex
    pthread_mutex_lock(&merge_lock);
    for (int d = 0; d < 10; d++) {
        global_counts[d] += local_counts[d];
    }
    pthread_mutex_unlock(&merge_lock);

    pthread_exit(NULL);
}

int main(void) {
    double t1, t2;

    // Load data
    if (!loadData("medium.bin")) {
        printf("Error loading data.\n");
        return -1;
    }

    // Initialize the global array and mutex
    for (int i = 0; i < 10; i++) global_counts[i] = 0;
    pthread_mutex_init(&merge_lock, NULL);

    pthread_t threads[NUM_THREADS];
    ThreadInfo ti[NUM_THREADS];

    // Work division
    int base = N / NUM_THREADS;
    int extra = N % NUM_THREADS;
    int index = 0;

    t1 = get_time_sec();

    // Create threads
    for (int t = 0; t < NUM_THREADS; t++) {
        ti[t].tid = t;
        ti[t].start = index;

        int size = base;
        if (t == NUM_THREADS - 1)
            size += extra; // last thread gets extra items

        ti[t].end = index + size;
        index += size;

        pthread_create(&threads[t], NULL, worker, &ti[t]);
    }

    // Join threads
    for (int t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    t2 = get_time_sec();

    // Output results
    for (int i = 1; i < 10; i++) {
        printf("There are %d %d's\n", global_counts[i], i);
    }

    printf("It took %f seconds for the whole thing to run\n", t2 - t1);

    pthread_mutex_destroy(&merge_lock);
    free(data);

    return 0;
}
