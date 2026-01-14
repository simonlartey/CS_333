/*
 * Author: Simon Lartey
 * Date: 11/12/25
 * Project: Signal Handling in C
 * Description: 
 *      Demonstrates how to handle the SIGINT signal (Ctrl-C) in C.
 *      The program installs a custom handler that prints a message
 *      when Ctrl-C is pressed, and then exits the program cleanly.
 * 
 * How to run:
 *      gcc sigint_handler.c -o sigint_handler
 *      ./sigint_handler
 */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void sigint_handler(int sig) {
    printf("\nInterrupted!\n");
    exit(0);
}

int main() {

    // Register our SIGINT handler
    signal(SIGINT, sigint_handler);

    printf("Running...\n");

    // Infinite loop (but controlled to avoid spamming terminal)
    while (1) {
        sleep(1);
    }

    return 0;
}
