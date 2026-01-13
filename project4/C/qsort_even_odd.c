/**
 * @file   qsort_even_odd.c
 * @brief  Sorts integers with even numbers first (descending) and odd numbers later (ascending).
 * 
 * Uses the C standard library function qsort() with a custom comparator to demonstrate
 * polymorphic behavior in C through function pointers.
 *
 * Author: Simon Lartey
 * Date:   10/28/2025
 *
 * How to compile: gcc qsort_even_odd.c -o qsort_even_odd
 * How to run:     ./qsort_even_odd
 */

#include <stdio.h>
#include <stdlib.h>

/* Comparator function used in qsort */
int comparator(const void *p, const void *q) {
    const int a = *(const int *)p;
    const int b = *(const int *)q;

    const int a_even = (a % 2 == 0);
    const int b_even = (b % 2 == 0);

    // Case 1: one even, one odd → even first
    if (a_even && !b_even) return -1;
    if (!a_even && b_even) return 1;

    // Case 2: both even → descending order
    if (a_even && b_even) return b - a;

    // Case 3: both odd → ascending order
    return a - b;
}

int main(int argc, char **argv) {
    int ary[] = {10, 11, 1, 8, 9, 0, 13, 4, 2, 7, 6, 3, 5, 12};
    int size = sizeof(ary) / sizeof(int);

    qsort(ary, size, sizeof(int), comparator);

    printf("The sorted array is: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", ary[i]);
    }
    printf("\n");

    return 0;
}
