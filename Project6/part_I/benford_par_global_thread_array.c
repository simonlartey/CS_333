/* benford_par_global_thread_array.c
 *
 * Parallel Benford counter:
 * Version (v): Global Array of Arrays, Grouped by Thread, No Mutex.
 * Each thread writes to its own row of a global 2D array (thread → row).
 * No mutexes are needed because no threads share memory.
 * After all threads finish, the main thread reduces the 2D array.
 *
 * Compile with:
 *     gcc -o benford_par_global_thread_array \
 *         my_timing.c benford_par_global_thread_array.c benford_helper.c \
 *         -lm -lpthread
 *
 * Run with:
 *     ./benford_par_global_thread_array
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "my_timing.h"

// External from helper file
extern int N;
extern double *data;
int loadData(char *filename);
int leadingDigit(double n);

#define NUM_THREADS 8

// Global output array
int global_counts[10];

// 2D local counters: one row per thread
int local_counts[NUM_THREADS][10];

// Thread info struct
typedef struct {
    int tid;
    int start;
    int end;
} ThreadInfo;

void *worker(void *arg) {
    ThreadInfo *ti = (ThreadInfo *)arg;

    // Local row for this thread
    int *my_row = local_counts[ti->tid];

    // Count leading digits locally with NO locking
    for (int i = ti->start; i < ti->end; i++) {
        int d = leadingDigit(data[i]);
        my_row[d]++;
    }
    pthread_exit(NULL);
}

int main(void) {
    double t1, t2;

    if (!loadData("medium.bin")) {
        printf("Error loading data.\n");
        return -1;
    }

    // Zero the global and local arrays
    for (int d = 0; d < 10; d++)
        global_counts[d] = 0;

    for (int t = 0; t < NUM_THREADS; t++)
        for (int d = 0; d < 10; d++)
            local_counts[t][d] = 0;

    pthread_t threads[NUM_THREADS];
    ThreadInfo ti[NUM_THREADS];

    // Divide work evenly
    int base = N / NUM_THREADS;
    int extra = N % NUM_THREADS;
    int index = 0;

    t1 = get_time_sec();

    // Start threads
    for (int t = 0; t < NUM_THREADS; t++) {
        ti[t].tid = t;
        ti[t].start = index;

        int size = base;
        if (t == NUM_THREADS - 1)
            size += extra;

        ti[t].end = index + size;
        index += size;

        pthread_create(&threads[t], NULL, worker, &ti[t]);
    }

    // Join threads
    for (int t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    // Final reduction: sum all local rows into global array
    for (int d = 0; d < 10; d++) {
        for (int t = 0; t < NUM_THREADS; t++) {
            global_counts[d] += local_counts[t][d];
        }
    }

    t2 = get_time_sec();

    // Print results
    for (int d = 1; d < 10; d++) {
        printf("There are %d %d's\n", global_counts[d], d);
    }

    printf("It took %f seconds for the whole thing to run\n", t2 - t1);

    free(data);
    return 0;
}
