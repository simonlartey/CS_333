/*
 * Author: Simon Lartey
 * Date: 11/12/25
 * Project: Signal Handling in C
 * Description:
 *      This program demonstrates how to handle a segmentation fault (SIGSEGV)
 *      using the signal() function. The program installs a handler for SIGSEGV,
 *      then deliberately dereferences a NULL pointer to trigger the fault. 
 *      The handler prints a message and terminates the program.
 *
 * How to run:
 *      gcc sigsegv_handler.c -o sigsegv_handler
 *      ./sigsegv_handler
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>


void sigsegv_handler(int signal) {
    printf("\nCaught signal %d (SIGSEGV): illegal memory access!\n", signal);
    printf("Terminating program...\n");
    exit(1);
}

int main() {

    // Register the SIGSEGV handler
    signal(SIGSEGV, sigsegv_handler);

    printf("About to dereference a NULL pointer...\n");

    int *ptr = NULL;

    printf("Pointer address: %p\n", ptr);

    // This triggers SIGSEGV
    printf("Dereferenced value: %d\n", *ptr);

    // This line will never be reached
    printf("This line will not execute.\n");

    return 0;
}
