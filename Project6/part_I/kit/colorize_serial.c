/*
 * colorize_serial.c
 *
 * Serial version of the colorize program.
 * Includes REPEAT to make timing comparable to multithreaded versions.
 *
 * Compile:
 *     gcc -o colorize_serial colorize_serial.c ppmIO.c my_timing.c -lpthread
 *
 * Run:
 *     ./colorize_serial IMG_4203.ppm
 */

#include <stdio.h>
#include <stdlib.h>
#include "ppmIO.h"
#include "my_timing.h"

#define REPEAT 20    // Number of times to repeat processing for timing

int main(int argc, char *argv[]) {
    Pixel *src;
    int rows, cols, colors;

    if (argc < 2) {
        printf("Usage: %s <image filename>\n", argv[0]);
        exit(-1);
    }

    src = ppm_read(&rows, &cols, &colors, argv[1]);
    if (!src) {
        printf("Unable to read file %s\n", argv[1]);
        exit(-1);
    }

    int total = rows * cols;

    double t1 = get_time_sec();

    for (int r = 0; r < REPEAT; r++) {
        for (int i = 0; i < total; i++) {
            src[i].r = src[i].r > 128 ? (220 + src[i].r)/2 : (30 + src[i].r)/2;
            src[i].g = src[i].g > 128 ? (220 + src[i].g)/2 : (30 + src[i].g)/2;
            src[i].b = src[i].b > 128 ? (220 + src[i].b)/2 : (30 + src[i].b)/2;
        }
    }

    double t2 = get_time_sec();
    printf("Serial time: %f sec\n", t2 - t1);

    ppm_write(src, rows, cols, colors, "bold.ppm");
    free(src);
    return 0;
}
