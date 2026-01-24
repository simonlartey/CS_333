/*
 * Author: Simon Lartey
 * Date: 11/13/25
 * Project: Memory Allocation Timing
 * Description:
 *      This program measures the average time required for malloc()
 *      to allocate different amounts of memory. It runs many trials
 *      for each size and reports the average time per call in a clean
 *      two-column format suitable for graphing (bytes, microseconds).
 *
 * Compile:
 *      gcc malloc_timing.c -o malloc_timing
 *
 * Run:
 *      ./malloc_timing > malloc_results.txt
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


double time_malloc(size_t bytes, int trials) {
    struct timeval start, end;

    // Perform an initial malloc to avoid counting allocator startup overhead
    void *tmp = malloc(bytes);
    free(tmp);

    gettimeofday(&start, NULL);

    for (int i = 0; i < trials; i++) {
        void *ptr = malloc(bytes);
        free(ptr);
    }

    gettimeofday(&end, NULL);

    double start_us = start.tv_sec * 1e6 + start.tv_usec;
    double end_us   = end.tv_sec   * 1e6 + end.tv_usec;

    double total_us = end_us - start_us;
    return total_us / trials;   // avg time per malloc in microseconds
}

int main() {
    int trials = 200000;   // number of malloc calls per test

    // Allocation sizes for the experiment
    size_t sizes[] = {
        10 * sizeof(int),          // extremely small
        100 * sizeof(int),         // small
        1000 * sizeof(int),        // ~4 KB
        10000 * sizeof(int),       // ~40 KB
        100000 * sizeof(int),      // ~400 KB
        500000 * sizeof(int),      // ~2 MB
        1000000 * sizeof(int),     // ~4 MB
        5000000 * sizeof(int)      // ~20 MB
    };

    int num_sizes = sizeof(sizes) / sizeof(size_t);

    
    printf("bytes avg_time_microseconds\n");

    // Print rows in: BYTES   TIME
    for (int i = 0; i < num_sizes; i++) {
        double avg_us = time_malloc(sizes[i], trials);
        printf("%zu %.6f\n", sizes[i], avg_us);
    }

    return 0;
}
