/**
 * File Name:   extension_2.c
 * Description: A short C program to generate a segmentation fault.
 * Author:      Simon Lartey
 * Date:        09/18/2025
 */


#include <stdio.h>
int main() {
    int *p = (int *)0x1;  // invalid, misaligned memory access
    *p = 5;               // bus error
    return 0;
}
