/*
 * Author: Simon Lartey
 * Date: 10/30/2025
 * Project: CS333 Project 04 - Extension
 * Description:
 *   Baseline version of the even-odd sorting program using qsort() with a
 *   simple comparator. This version tests performance on a large dataset
 *   (1,000,000 integers) to compare with the optimized implementation.
 *
 * How to compile:
 *   gcc qsort_even_odd_baseline.c -O2 -o baseline
 *
 * How to run:
 *   ./baseline
 *
 * To compare runtime performance with the optimized version:
 *   gcc qsort_even_odd_optimized.c -O2 -o optimized
 *   time ./baseline
 *   time ./optimized
 *
 * The 'time' command measures user, system, and total execution time
 * to evaluate performance differences between the two implementations.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Comparator function for qsort.
 * Sorts even numbers first in descending order,
 * followed by odd numbers in ascending order.
 */
int comparator(const void *p, const void *q) {
    const int a = *(const int *)p;
    const int b = *(const int *)q;

    const int a_even = (a % 2 == 0);
    const int b_even = (b % 2 == 0);

    // Even before odd
    if (a_even && !b_even) return -1;
    if (!a_even && b_even) return 1;

    // Both even → descending
    if (a_even && b_even) return b - a;

    // Both odd → ascending
    return a - b;
}

int main(void) {
    const int SIZE = 1000000; // One million integers
    int *arr = malloc(SIZE * sizeof(int));
    if (!arr) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return 1;
    }

    srand(42); // Fixed seed for reproducible results
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 1000;
    }

    clock_t start = clock();
    qsort(arr, SIZE, sizeof(int), comparator);
    clock_t end = clock();

    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Baseline sorting completed in %.4f seconds.\n", elapsed);

    printf("First 20 sorted numbers: ");
    for (int i = 0; i < 20; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}
