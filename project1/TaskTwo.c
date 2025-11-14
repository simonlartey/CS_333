/**
 * File Name:   TaskTwo.c
 * Description: Program to examine the layout of stack variables in memory.
 *              Declares several variables of different types, then uses an
 *              unsigned char pointer to print raw byte contents sequentially.
 * Author:      Simon Lartey
 * Date:        09/18/2025
 */

#include <stdio.h>

int main(int arg, char * argv[]){
  // Declare variables of different data types
  char character = (char) 0xA1;
  short short_integer = (short) 0xA1B2;
  int integer = (int) 0xA1B2C3D4;
  long long_integer = (long) 0xA1B2C3D4E5F6A7B8;

  // Pointer to inspect raw memory
  unsigned char * ptr;
  ptr = (unsigned char *) &ptr;

  // Print first 100 bytes from the pointer's location
  for (int i = 0; i < 100; i++){
    printf("%d: %02X\n", i, ptr[i]);
  }

  return 0;
}
