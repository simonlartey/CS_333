/**
 * @file   qsort_even_odd_optimized.c
 * @brief  Optimized comparator for sorting even numbers (descending)
 *         before odd numbers (ascending) using fewer conditionals.
 *
 * Author: Simon Lartey
 * Date:   10/29/2025
 *
 * How to compile: gcc qsort_even_odd_optimized.c -O2 -o optimized
 * How to run:     ./optimized
 *
 * To compare runtime performance with the baseline version:
 *   gcc qsort_even_odd_baseline.c -O2 -o baseline
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
 * Optimized comparator function for qsort.
 * - Even numbers come first.
 * - Evens are sorted descending.
 * - Odds are sorted ascending.
 *
 * Uses arithmetic instead of nested if-statements to reduce branching.
 */
int fast_comparator(const void *p, const void *q) {
    const int a = *(const int *)p;
    const int b = *(const int *)q;

    // Determine parity (0 for even, 1 for odd)
    const int a_odd = a & 1;
    const int b_odd = b & 1;

    // Primary key: even before odd
    if (a_odd != b_odd)
        return a_odd - b_odd; // even (0) → smaller, comes first

    // Secondary key:
    // - Both even → descending
    // - Both odd  → ascending
    // Multiplying difference by direction (-1 for even, +1 for odd)
    const int direction = a_odd ? 1 : -1;
    return direction * (a - b);
}

int main(void) {
    // Generate a larger array to test performance difference
    const int SIZE = 1000000;
    int *arr = malloc(SIZE * sizeof(int));
    srand(42);

    for (int i = 0; i < SIZE; i++)
        arr[i] = rand() % 1000;

    clock_t start = clock();
    qsort(arr, SIZE, sizeof(int), fast_comparator);
    clock_t end = clock();

    printf("Sorting completed in %.4f seconds.\n",
           (double)(end - start) / CLOCKS_PER_SEC);

    // Optional: print first 20 elements to verify correctness
    printf("First 20 sorted numbers: ");
    for (int i = 0; i < 20; i++)
        printf("%d ", arr[i]);
    printf("\n");

    free(arr);
    return 0;
}
