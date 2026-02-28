// benford_helper.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <math.h>

int N = 0;
double *data = NULL;

// Load the binary data file
int loadData(char *filename) {
    FILE *fp;

    if(filename != NULL && strlen(filename))
        fp = fopen(filename, "r");
    else
        return -1;

    if (!fp)
        return -1;

    fread(&N, sizeof(int), 1, fp);
    data = (double*)malloc(sizeof(double) * N);
    fread(data, sizeof(double), N, fp);
    fclose(fp);
    return 1;
}

// Return the leading digit of n
int leadingDigit(double n) {
    if (fabs(n) == 1.0)
        return 1;
    else if (fabs(n) == 0.0)
        return 0;
    else if (fabs(n) < 1.0) {
        double tmp = fabs(n);
        while (tmp < 1.0) tmp *= 10.0;
        return (int)floor(tmp);
    }
    else {
        long long unsigned in = (long long unsigned) floor(fabs(n));
        while (in > 9) in /= 10;
        return in;
    }
}
