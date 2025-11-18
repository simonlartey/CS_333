/**
 * File Name:   extensionTwo.c
 * Description: Find the floating point number where adding 1 has no effect
 *              for float, double, and long double types.
 * Author:      Simon Lartey
 * Date:        09/18/2025
 */
#include <stdio.h>
#include <math.h>

int main(void) {
    // ----- Float -----
    float f = 1.0f;
    int f_exp = 0;
    while (f + 1 != f) {
        f *= 2.0f;
        f_exp++;
    }
    printf("Float cutoff: %.0f (≈ 2^%d)\n", f, f_exp);

    // ----- Double -----
    double d = 1.0;
    int d_exp = 0;
    while (d + 1 != d) {
        d *= 2.0;
        d_exp++;
    }
    printf("Double cutoff: %.0f (≈ 2^%d)\n", d, d_exp);

    // ----- Long Double -----
    long double ld = 1.0L;
    int ld_exp = 0;
    while (ld + 1 != ld) {
        ld *= 2.0L;
        ld_exp++;
    }
    printf("Long double cutoff: %.0Lf (≈ 2^%d)\n", ld, ld_exp);

    return 0;
}
