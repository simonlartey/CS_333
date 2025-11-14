/**
 * File Name:   TaskFour.c
 * Description: Program to investigate struct memory layout and alignment 
 *              by using different variable orders and types.
 * Author:      Simon Lartey
 * Date:        09/28/25
 */
#include <stdio.h>
#include <stdlib.h>

// Variation 1: includes char, short, int
typedef struct Structure1 {
    char character;       // 1 byte
    short short_integer;  // 2 bytes
    int integer;          // 4 bytes
} Structure1;

// Variation 2: includes char twice, and an int
typedef struct Structure2 {
    char c1;              // 1 byte
    int integer;          // 4 bytes
    char c2;              // 1 byte
    short short_integer;  // 2 bytes
} Structure2;

// Variation 3: mix of short, char, and double
typedef struct Structure3 {
    short short_integer;  // 2 bytes
    char character;       // 1 byte
    double double_number; // 8 bytes
} Structure3;

int main(int arg, char *argv[]) {
    unsigned char *ptr;

    // Structure 1
    Structure1 *s1 = (Structure1 *) malloc(sizeof(Structure1));
    s1->character = (char) 0x41;       // 'A'
    s1->short_integer = (short) 0x1234;
    s1->integer = (int) 0x11223344;

    printf("Structure1 (char, short, int) Size: %zu bytes\n", sizeof(Structure1));
    ptr = (unsigned char *) s1;
    for (int i = 0; i < sizeof(Structure1); i++) {
        printf("%d: %02X\n", i, ptr[i]);
    }

    // Structure 2
    Structure2 *s2 = (Structure2 *) malloc(sizeof(Structure2));
    s2->c1 = (char) 0x42;              // 'B'
    s2->integer = (int) 0x55667788;
    s2->c2 = (char) 0x43;              // 'C'
    s2->short_integer = (short) 0x9ABC;

    printf("\n\nStructure2 (char, int, char, short) Size: %zu bytes\n", sizeof(Structure2));
    ptr = (unsigned char *) s2;
    for (int i = 0; i < sizeof(Structure2); i++) {
        printf("%d: %02X\n", i, ptr[i]);
    }

    // Structure 3
    Structure3 *s3 = (Structure3 *) malloc(sizeof(Structure3));
    s3->short_integer = (short) 0xDEAD;
    s3->character = (char) 0x44;       // 'D'
    s3->double_number = (double) 123.456;

    printf("\n\nStructure3 (short, char, double) Size: %zu bytes\n", sizeof(Structure3));
    ptr = (unsigned char *) s3;
    for (int i = 0; i < sizeof(Structure3); i++) {
        printf("%d: %02X\n", i, ptr[i]);
    }

    free(s1);
    free(s2);
    free(s3);
    return 0;
}
