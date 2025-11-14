/**
 * File Name:   TaskOne.c
 * Description: Program to declare variables of different basic types and 
 *              examine how they are stored in memory. Uses an unsigned char* 
 *              to print the raw byte layout of each type in hexadecimal. 
 * Author:      Simon Lartey
 * Date:        09/18/2025
 */

#include <stdio.h>

int main(int arg, char *argv[]) {
    // Declare variables of different types with chosen hex values
    char character       = (char) 0x7E;             
    short short_integer  = (short) 0x55AA;          
    int integer          = (int) 0x11223344;        
    long long_integer    = (long) 0x5566778899AABBCC; 
    float float_number   = (float) 0x40490FDB;     
    double double_number = (double) 0x400921FB54442D18;

    unsigned char *ptr;  // Pointer for inspecting raw memory

    // Print memory layout of char
    printf("char:\n");
    ptr = (unsigned char *) &character;
    for (int i = 0; i < sizeof(character); i++) {
        printf("%d: %02X\n", i, ptr[i]);
    }

    // Print memory layout of short
    printf("\nshort:\n");
    ptr = (unsigned char *) &short_integer;
    for (int i = 0; i < sizeof(short_integer); i++) {
        printf("%d: %02X\n", i, ptr[i]);
    }

    // Print memory layout of int
    printf("\ninteger:\n");
    ptr = (unsigned char *) &integer;
    for (int i = 0; i < sizeof(integer); i++) {
        printf("%d: %02X\n", i, ptr[i]);
    }

    // Print memory layout of long
    printf("\nlong:\n");
    ptr = (unsigned char *) &long_integer;
    for (int i = 0; i < sizeof(long_integer); i++) {
        printf("%d: %02X\n", i, ptr[i]);
    }

    // Print memory layout of float
    printf("\nfloat:\n");
    ptr = (unsigned char *) &float_number;
    for (int i = 0; i < sizeof(float_number); i++) {
        printf("%d: %02X\n", i, ptr[i]);
    }

    // Print memory layout of double
    printf("\ndouble:\n");
    ptr = (unsigned char *) &double_number;
    for (int i = 0; i < sizeof(double_number); i++) {
        printf("%d: %02X\n", i, ptr[i]);
    }

    return 0;
}
