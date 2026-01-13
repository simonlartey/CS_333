/**
 * @file   factorial.c
 * @brief  Demonstrates use of a function pointer to compute factorials.
 * 
 * Defines a factorial function and shows how to call it using a function pointer.
 * The user provides an integer N as a command-line argument, and the program
 * computes N! and prints the result.
 * 
 * Author: Simon Lartey
 * Date:   10/28/2025
 *
 * How to compile: gcc factorial.c -o factorial
 * How to run:     ./factorial <integer>
 */


#include <stdio.h>
#include <stdlib.h>

/**
 * Computes the factorial of a non-negative integer.
 *
 * @param n A non-negative integer whose factorial is to be computed.
 * @return The factorial of n as an integer.
 */
int factorial(const int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

int main(int argc, char **argv) {
    // Check for correct number of arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Convert argument to integer
    int number = atoi(argv[1]);

    // Validate input
    if (number < 0) {
        fprintf(stderr, "Error: Input must be a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    // Declare function pointer and assign factorial to it
    int (*calc)(const int) = factorial;

    // Compute factorial using the function pointer
    int result = calc(number);

    // Display result
    printf("%d! = %d\n", number, result);

    return EXIT_SUCCESS;
}
