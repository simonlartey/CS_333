/*
 * colorize_1thread.c
 *
 * Pthreads version using ONE worker thread.
 * Now includes REPEAT loops so timing is comparable to 2-thread and 4-thread versions.
 *
 * Compile:
 *     gcc -o colorize_1thread colorize_1thread.c ppmIO.c my_timing.c -lpthread
 *
 * Run:
 *     ./colorize_1thread IMG_4203.ppm
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

    Work w = { src, 0, total };
    pthread_t t;

    double t1 = get_time_sec();
    pthread_create(&t, NULL, worker, &w);
    pthread_join(t, NULL);
    double t2 = get_time_sec();

    printf("1-thread time: %f sec\n", t2 - t1);

    ppm_write(src, rows, cols, colors, "bold.ppm");
    free(src);
    return 0;
}
