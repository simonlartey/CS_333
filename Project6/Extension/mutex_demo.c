/*
 * Mutex Demonstration Extension
 * Using pthreads to safely increment a shared counter
 * how to run and compile:
 *      gcc -o mutex_demo mutex_demo.c -lpthread
 *        ./mutex_demo
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 8
#define INCREMENTS 100000

int counter = 0;              // shared variable
pthread_mutex_t lock;         // mutex

void *worker(void *arg) {
    for (int i = 0; i < INCREMENTS; i++) {
        pthread_mutex_lock(&lock);    // enter critical section
        counter++;                    // shared update
        pthread_mutex_unlock(&lock);  // exit critical section
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, worker, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    printf("Final counter: %d (expected %d)\n",
           counter, NUM_THREADS * INCREMENTS);

    return 0;
}
