/* benford_par_global_digit_array.c
 * Global Counter Array of Arrays, Grouped by Digit, NO mutexes.
 *
 * Compile with:
 * gcc -o benford_par_global_digit_array \
 *     my_timing.c benford_par_global_digit_array.c benford_helper.c \
 *     -lm -lpthread
 * 
 * Run with:
 * ./benford_par_global_digit_array
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "my_timing.h"

// External globals imported from helper
extern int N;
extern double *data;
int loadData(char *filename);
int leadingDigit(double n);

#define NUM_THREADS 8

// Global 2D array grouped by digit
int digit_counts[10][NUM_THREADS];

// Final global result after reduction
int global_counts[10];

// Thread info
typedef struct {
    int tid;
    int start;
    int end;
} ThreadInfo;

void *worker(void *arg) {
    ThreadInfo *ti = (ThreadInfo *)arg;
    int tid = ti->tid;

    // Count digits locally (each thread writes to its own column)
    for (int i = ti->start; i < ti->end; i++) {
        int d = leadingDigit(data[i]);
        digit_counts[d][tid]++;
    }

    pthread_exit(NULL);
}

int main(void) {
    double t1, t2;

    // Load data
    if (!loadData("medium.bin")) {
        printf("Error loading data.\n");
        return -1;
    }

    // Initialize arrays
    for (int d = 0; d < 10; d++) {
        global_counts[d] = 0;
        for (int t = 0; t < NUM_THREADS; t++) {
            digit_counts[d][t] = 0;
        }
    }

    pthread_t threads[NUM_THREADS];
    ThreadInfo ti[NUM_THREADS];

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
            size += extra;

        ti[t].end = index + size;
        index += size;

        pthread_create(&threads[t], NULL, worker, &ti[t]);
    }

    // Join all threads
    for (int t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    // Reduction step — main thread only
    for (int d = 0; d < 10; d++) {
        for (int t = 0; t < NUM_THREADS; t++) {
            global_counts[d] += digit_counts[d][t];
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
