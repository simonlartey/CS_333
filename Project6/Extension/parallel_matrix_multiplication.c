/*
 * Parallel Matrix Multiplication Extension
 * Using pthreads – each thread computes a set of rows
 * how to run and compile:
 *      gcc -o parallel_matrix_multiplication parallel_matrix_multiplication.c -lpthread
 *        ./parallel_matrix_multiplication
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int tid;
    int start_row;
    int end_row;
    int n;
    int **A;
    int **B;
    int **C;
} ThreadInfo;

void *worker(void *arg) {
    ThreadInfo *info = (ThreadInfo *)arg;
    int n = info->n;

    for (int i = info->start_row; i < info->end_row; i++) {
        for (int j = 0; j < n; j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                sum += info->A[i][k] * info->B[k][j];
            }
            info->C[i][j] = sum;
        }
    }
    return NULL;
}

// Utility: allocate matrix
int **alloc_matrix(int n) {
    int **M = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        M[i] = calloc(n, sizeof(int));
    return M;
}

int main() {
    int n = 4;                 // matrix size
    int num_threads = 4;

    pthread_t threads[num_threads];
    ThreadInfo info[num_threads];

    int **A = alloc_matrix(n);
    int **B = alloc_matrix(n);
    int **C = alloc_matrix(n);

    // Example matrices
    int counter = 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = counter++;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            B[i][j] = (i == j) ? 1 : 0;  // identity matrix

    // Divide rows across threads
    int base = n / num_threads;
    int extra = n % num_threads;
    int row = 0;

    for (int t = 0; t < num_threads; t++) {
        int size = base + (t < extra ? 1 : 0);

        info[t].tid = t;
        info[t].start_row = row;
        info[t].end_row = row + size;
        info[t].n = n;
        info[t].A = A;
        info[t].B = B;
        info[t].C = C;

        pthread_create(&threads[t], NULL, worker, &info[t]);
        row += size;
    }

    for (int t = 0; t < num_threads; t++)
        pthread_join(threads[t], NULL);

    // Print result
    printf("Result of A × B:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

    return 0;
}
