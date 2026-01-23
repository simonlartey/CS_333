
/* 
 * Author: Simon Lartey
 * Date: 11/16/2025
 * File: profiler_wordcounter.c
 *
 * Description:
 *     A word-frequency counter built on a hash map, instrumented for
 *     profiling using the -finstrument-functions compiler flag. This
 *     program processes an input text file, normalizes each token,
 *     inserts it into a hash map, and triggers profiling hooks in
 *     profiler.c to log function entry and exit events. The profiling
 *     output is written to profile_log.txt.
 * How to compile:
 *     gcc profiler_wordcounter.c hashmap.c profiler.c -finstrument-functions -o profiler_wc
 *     ./profiler_wc wctest.txt  
*/

// profiler_wordcounter.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hashmap.h"

// Convert to lowercase
void to_lower(char *s) {
    for (int i = 0; s[i]; i++)
        s[i] = tolower(s[i]);
}

// Remove punctuation at start or end
void strip(char *s) {
    int len = strlen(s);
    while (len > 0 && ispunct((unsigned char)s[len - 1]))
        s[--len] = '\0';

    int shift = 0;
    while (s[shift] && ispunct((unsigned char)s[shift]))
        shift++;

    if (shift > 0)
        memmove(s, s + shift, strlen(s + shift) + 1);
}

int main(int argc, char **argv) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    HashMap *hm = hm_create(5000);
    char buffer[256];

    
    while (fscanf(fp, "%255s", buffer) == 1) {
        strip(buffer);
        to_lower(buffer);

        if (strlen(buffer) > 0)
            hm_insert(hm, buffer);
    }
    

    hm_print_top(hm, 20);

    hm_free(hm);
    fclose(fp);
    return 0;
}
