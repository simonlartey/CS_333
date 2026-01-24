/*
 * Author: Simon Lartey
 * Date: 11/12/25
 * Project: Signal Handling in C
 * Description:
 *      This program demonstrates how to handle a floating point exception (SIGFPE)
 *      using the signal() function. If the user attempts to divide an integer
 *      by zero, the SIGFPE handler runs, prints a message, and allows the user
 *      to enter a new (non-zero) divisor so the program can continue normally.
 *
 * How to run:
 *      gcc sigfpe_handler.c -o sigfpe_handler
 *      ./sigfpe_handler
 */

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int dividend;
int divisor;


void sigfpe_handler(int signal) {
    printf("\nEncountered signal %d (SIGFPE): division by zero!\n", signal);

    printf("Please enter a non-zero divisor: ");
    scanf("%d", &divisor);

    if (divisor != 0) {
        // Return to allow main() to continue normally
        return;
    }

    printf("Still invalid (zero) divisor.\nTerminating program...\n");
    exit(1);
}

int main() {

    // Install the SIGFPE handler
    signal(SIGFPE, sigfpe_handler);

    printf("Enter value for dividend: ");
    scanf("%d", &dividend);

    printf("Enter value for divisor: ");
    scanf("%d", &divisor);

    // This may trigger SIGFPE if divisor is zero
    int quotient = dividend / divisor;

    printf("%d divided by %d is equal to %d.\n",
           dividend, divisor, quotient);

    return 0;
}
