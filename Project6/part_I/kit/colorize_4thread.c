/*
 * colorize_4thread.c
 *
 * Pthreads version using FOUR worker threads.
 * Includes REPEAT loops to increase runtime so timing comparisons
 * against 1-thread and serial versions are meaningful.
 *
 * Compile:
 *     gcc -o colorize_4thread colorize_4thread.c ppmIO.c my_timing.c -lpthread
 *
 * Run:
 *     ./colorize_4thread IMG_4203.ppm
 *
 * Output:
 *     bold.ppm
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "ppmIO.h"
#include "my_timing.h"

#define NUM_THREADS 4
#define REPEAT 20   // repeat processing for stable timing

typedef struct {
    Pixel *img;
    int start;
    int end;
} Work;

void *worker(void *arg) {
    Work *w = (Work*)arg;

    for (int r = 0; r < REPEAT; r++) {
        for (int i = w->start; i < w->end; i++) {

            unsigned char r_val = w->img[i].r;
            unsigned char g_val = w->img[i].g;
            unsigned char b_val = w->img[i].b;

            w->img[i].r = (r_val > 128) ? (220 + r_val)/2 : (30 + r_val)/2;
            w->img[i].g = (g_val > 128) ? (220 + g_val)/2 : (30 + g_val)/2;
            w->img[i].b = (b_val > 128) ? (220 + b_val)/2 : (30 + b_val)/2;
        }
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    Pixel *src;
    int rows, cols, colors;

    if (argc < 2) {
        printf("Usage: %s <image>\n", argv[0]);
        exit(-1);
    }

    src = ppm_read(&rows, &cols, &colors, argv[1]);
    if (!src) {
        printf("Unable to read file %s\n", argv[1]);
        exit(-1);
    }

    int total = rows * cols;
    int chunk = total / NUM_THREADS;

    Work work[NUM_THREADS];
    pthread_t threads[NUM_THREADS];

    // Divide image evenly across threads
    for (int i = 0; i < NUM_THREADS; i++) {
        work[i].img = src;
        work[i].start = i * chunk;
        work[i].end = (i == NUM_THREADS - 1 ? total : (i + 1) * chunk);
    }

    double t1 = get_time_sec();

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_create(&threads[i], NULL, worker, &work[i]);

    // Wait for all threads
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    double t2 = get_time_sec();
    printf("4-thread time: %f sec\n", t2 - t1);

    ppm_write(src, rows, cols, colors, "bold.ppm");
    free(src);

    return 0;
}
