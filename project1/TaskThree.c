/**
 * File Name:   TaskThree.c
 * Description: Program to demonstrate the effect of freeing vs. not freeing 
 *              allocated memory. Repeatedly allocates small chunks of memory 
 *              in an infinite loop to observe memory usage.
 * Author:      Simon Lartey
 * Date:        09/18/2025
 */

#include <stdio.h>
#include <stdlib.h>

int main(int arg, char *argv[]) {
    unsigned char * ptr;

    // Allocate repeatedly without freeing (commented out to avoid memory hogging)
    // while (1) {
    //     ptr = (unsigned char *) malloc(sizeof(int));
    // }

    // Allocate and immediately free memory in each loop iteration
    while (1) {
        ptr = (unsigned char *) malloc(sizeof(int));
        free(ptr);
    }

    return 0;
}
