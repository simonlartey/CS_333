/*
 * File: profiler.c
 * Author: Simon Lartey
 * Date: 11/16/2025
 *
 * Description:
 *     Implements the profiling hooks required by the 
 *     -finstrument-functions flag. Each function entry and exit
 *     is logged with a timestamp to profile_log.txt, using 
 *     constructor and destructor attributes for automatic setup
 *     and cleanup. This file is linked with instrumented programs
 *     such as profiler_wordcounter.c.
 * How to run: NA
 */
#include <stdio.h>
#include <stdint.h>
#include <time.h>

static FILE *logfile = NULL;

// Automatically runs before main()
__attribute__((constructor))
void profiler_start() {
    logfile = fopen("profile_log.txt", "w");
}

// Automatically runs after program exit
__attribute__((destructor))
void profiler_end() {
    if (logfile) fclose(logfile);
}

// Called at FUNCTION ENTRY
void __cyg_profile_func_enter(void *func, void *caller)
    __attribute__((no_instrument_function));

void __cyg_profile_func_enter(void *func, void *caller) {
    if (!logfile) return;

    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    fprintf(logfile, "E %p %p %ld.%09ld\n",
            func, caller, ts.tv_sec, ts.tv_nsec);
}

// Called at FUNCTION EXIT
void __cyg_profile_func_exit(void *func, void *caller)
    __attribute__((no_instrument_function));

void __cyg_profile_func_exit(void *func, void *caller) {
    if (!logfile) return;

    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    fprintf(logfile, "X %p %p %ld.%09ld\n",
            func, caller, ts.tv_sec, ts.tv_nsec);
}
