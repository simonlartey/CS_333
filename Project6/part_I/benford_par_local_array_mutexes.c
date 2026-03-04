/* benford_par_local_array_mutexes.c
 *
 * Parallel Benford counter — Assignment Version (iv)
 *
 * Each thread:
 *   1. Uses a local counter array (local_counts[10]) → no locking
 *   2. After counting, uses an ARRAY OF MUTEXES (one per digit)
 *      to merge its results into the global_counts.
 *
 * Compile with:
 * gcc -o benford_par_local_array_mutexes \
 *     my_timing.c benford_par_local_array_mutexes.c benford_helper.c \
 *     -lm -lpthread
 * 
 * Run with:
 * ./benford_par_local_array_mutexes
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

// Global counter array
int global_counts[10];

// Array of mutexes (one per digit 0–9)
pthread_mutex_t digit_lock[10];

// Thread info struct
typedef struct {
    int tid;
    int start;
    int end;
} ThreadInfo;

void *worker(void *arg) {
    ThreadInfo *ti = (ThreadInfo *)arg;

    // Local array (NO LOCKING for local work)
    int local_counts[10] = {0};

    // Count leading digits locally
    for (int i = ti->start; i < ti->end; i++) {
        int d = leadingDigit(data[i]);
        local_counts[d]++;
    }

    // Merge results into global_counts using ARRAY of mutexes
    for (int d = 0; d < 10; d++) {
        pthread_mutex_lock(&digit_lock[d]);
        global_counts[d] += local_counts[d];
        pthread_mutex_unlock(&digit_lock[d]);
    }

    pthread_exit(NULL);
}

int main(void) {
    double t1, t2;

    if (!loadData("medium.bin")) {
        printf("Error loading data.\n");
        return -1;
    }

    // Initialize globals
    for (int i = 0; i < 10; i++)
        global_counts[i] = 0;

    // Initialize 10 mutexes
    for (int i = 0; i < 10; i++)
        pthread_mutex_init(&digit_lock[i], NULL);

    pthread_t threads[NUM_THREADS];
    ThreadInfo ti[NUM_THREADS];

    int base = N / NUM_THREADS;
    int extra = N % NUM_THREADS;
    int index = 0;

    t1 = get_time_sec();

    // Spawn threads
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

    // Join all threads
    for (int t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    t2 = get_time_sec();

    // Print results
    for (int d = 1; d < 10; d++) {
        printf("There are %d %d's\n", global_counts[d], d);
    }
    printf("It took %f seconds for the whole thing to run\n", t2 - t1);

    // Cleanup
    for (int i = 0; i < 10; i++)
        pthread_mutex_destroy(&digit_lock[i]);

    free(data);

    return 0;
}
