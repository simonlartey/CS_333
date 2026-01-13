/*
 * Author: Simon Lartey
 * Date: 10/31/2025
 * Project: CS333 Project 04 - Extension
 * Description:
 *   This program implements the MergeSort algorithm in C to demonstrate
 *   how to manually build a divide-and-conquer sorting algorithm.
 *   It recursively divides the array into subarrays, sorts them, and merges
 *   them back into a fully sorted list.
 *
 * How to compile:
 *   gcc merge_sort.c -O2 -o merge_sort
 *
 * How to run:
 *   ./merge_sort
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Merge helper using a shared temporary buffer */
void merge(int *arr, int *temp, int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        temp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (i = left; i <= right; i++) arr[i] = temp[i];
}

void mergeSortHelper(int *arr, int *temp, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(arr, temp, left, mid);
        mergeSortHelper(arr, temp, mid + 1, right);
        merge(arr, temp, left, mid, right);
    }
}

void mergeSort(int *arr, int size) {
    int *temp = malloc(size * sizeof(int));
    if (!temp) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        exit(1);
    }
    mergeSortHelper(arr, temp, 0, size - 1);
    free(temp);
}

int main(void) {
    const int SIZE = 100000;
    int *arr = malloc(SIZE * sizeof(int));
    if (!arr) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        return 1;
    }

    srand(42);
    for (int i = 0; i < SIZE; i++) arr[i] = rand() % 1000000;

    printf("Sorting %d integers using optimized MergeSort...\n", SIZE);

    clock_t start = clock();
    mergeSort(arr, SIZE);
    clock_t end = clock();

    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("MergeSort completed in %.4f seconds.\n", elapsed);

    printf("First 20 sorted numbers: ");
    for (int i = 0; i < 20; i++) printf("%d ", arr[i]);
    printf("\n");

    free(arr);
    return 0;
}
