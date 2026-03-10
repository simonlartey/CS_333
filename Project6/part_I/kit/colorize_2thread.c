/*
 * colorize_2thread.c
 *
 * Pthreads version using TWO worker threads.
 * Now includes REPEAT loops so timing is comparable to 1-thread and 4-thread versions.
 *
 * Compile:
 *     gcc -o colorize_2thread colorize_2thread.c ppmIO.c my_timing.c -lpthread
 *
 * Run:
 *     ./colorize_2thread IMG_4203.ppm
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "ppmIO.h"
#include "my_timing.h"

#define REPEAT 20

typedef struct {
    Pixel *img;
    int start;
    int end;
} Work;

void *worker(void *arg) {
    Work *w = (Work*)arg;

    for (int r = 0; r < REPEAT; r++) {
        for (int i = w->start; i < w->end; i++) {
            w->img[i].r = w->img[i].r > 128 ? (220 + w->img[i].r)/2 : (30 + w->img[i].r)/2;
            w->img[i].g = w->img[i].g > 128 ? (220 + w->img[i].g)/2 : (30 + w->img[i].g)/2;
            w->img[i].b = w->img[i].b > 128 ? (220 + w->img[i].b)/2 : (30 + w->img[i].b)/2;
        }
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc < 2) { printf("Usage: %s <image>\n", argv[0]); exit(-1); }

    Pixel *src;
    int rows, cols, colors;

    src = ppm_read(&rows, &cols, &colors, argv[1]);
    if (!src) { printf("Unable to read file %s\n", argv[1]); exit(-1); }

    int total = rows * cols;
    int mid = total / 2;

    Work w[2] = {
        { src, 0, mid },
        { src, mid, total }
    };

    pthread_t t[2];

    double t1 = get_time_sec();
    pthread_create(&t[0], NULL, worker, &w[0]);
    pthread_create(&t[1], NULL, worker, &w[1]);

    pthread_join(t[0], NULL);
    pthread_join(t[1], NULL);
    double t2 = get_time_sec();

    printf("2-thread time: %f sec\n", t2 - t1);

    ppm_write(src, rows, cols, colors, "bold.ppm");
    free(src);
    return 0;
}
