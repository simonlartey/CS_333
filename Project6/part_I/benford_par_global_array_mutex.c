/* benford_par_global_array_mutex.c
 *
 * Parallel Benford counter:
 * Version (ii): Global counter array protected by an ARRAY of mutexes
 * (one mutex per digit).
 * 
 * 
 * Compile with:
 * gcc -o benford_par_global_array_mutex \
 *  my_timing.c benford_par_global_array_mutex.c benford_helper.c \
 *  -lm -lpthread
 * Run with:
 *
 *  ./benford_par_global_array_mutex
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "my_timing.h"

// External variables/functions provided by benford_helper.c
extern int N;
extern double *data;
int loadData(char *filename);
int leadingDigit(double n);

#define NUM_THREADS 8

// Global array and one mutex per digit
int global_counts[10];
pthread_mutex_t lock[10];

// Thread info struct
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

        // Lock only the mutex for that specific digit
        pthread_mutex_lock(&lock[d]);
        global_counts[d]++;
        pthread_mutex_unlock(&lock[d]);
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    double t1, t2;

    // Load data from binary file
    if (!loadData("medium.bin")) {
        printf("Error loading data.\n");
        return -1;
    }

    // Initialize the global counts and the 10 mutexes
    for (int i = 0; i < 10; i++) {
        global_counts[i] = 0;
        pthread_mutex_init(&lock[i], NULL);
    }

    pthread_t threads[NUM_THREADS];
    ThreadInfo ti[NUM_THREADS];

    // Split the work evenly among the threads
    int base = N / NUM_THREADS;
    int extra = N % NUM_THREADS;
    int index = 0;

    t1 = get_time_sec();

    for (int t = 0; t < NUM_THREADS; t++) {
        ti[t].tid = t;
        ti[t].start = index;

        int size = base;
        if (t == NUM_THREADS - 1) {
            size += extra; // last thread gets the remainder
        }

        ti[t].end = index + size;
        index += size;

        pthread_create(&threads[t], NULL, worker, &ti[t]);
    }

    // Wait for all threads to complete
    for (int t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    t2 = get_time_sec();

    // Print results like the sequential version
    for (int d = 1; d < 10; d++) {
        printf("There are %d %d's\n", global_counts[d], d);
    }

    printf("It took %f seconds for the whole thing to run\n", t2 - t1);

    // Clean up
    for (int i = 0; i < 10; i++) {
        pthread_mutex_destroy(&lock[i]);
    }

    free(data);

    return 0;
}
