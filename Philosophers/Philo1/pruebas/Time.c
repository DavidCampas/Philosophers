/*#include <stdio.h>
#include <sys/time.h>

int main() {
    struct timeval tv;

    gettimeofday(&tv, NULL);

    printf("Segundos: %ld\n", tv.tv_sec);
    printf("Microsegundos: %ld\n", tv.tv_usec);

    return 0;
}*/

#include <stdio.h>
#include <sys/time.h>  // This includes the declaration for gettimeofday
#include <time.h>
#include <unistd.h>

#define NUM_CALLS 100
#define BOLD "\033[1m"
#define GOLD "\033[0;33m"
#define RESET "\033[0m"

void foo(void) {
    // Empty function
}

int main(void)
{
    struct timespec start_ts, end_ts;
    double elapsed_usleep_us, elapsed_usleep_ns;
    double elapsed_gettimeofday_us, elapsed_gettimeofday_ns;
    double elapsed_foo_us, elapsed_foo_ns;

    // Measure usleep
    clock_gettime(CLOCK_MONOTONIC, &start_ts);
    for (int i = 0; i < NUM_CALLS; i++)
        usleep(0);
    clock_gettime(CLOCK_MONOTONIC, &end_ts);
    elapsed_usleep_ns = (end_ts.tv_sec - start_ts.tv_sec) * 1e9 + (end_ts.tv_nsec - start_ts.tv_nsec);
    elapsed_usleep_us = elapsed_usleep_ns / 1e3;

    // Measure gettimeofday
    clock_gettime(CLOCK_MONOTONIC, &start_ts);
    struct timeval tmp;
    for (int i = 0; i < NUM_CALLS; i++)
        gettimeofday(&tmp, NULL);
    clock_gettime(CLOCK_MONOTONIC, &end_ts);
    elapsed_gettimeofday_ns = (end_ts.tv_sec - start_ts.tv_sec) * 1e9 + (end_ts.tv_nsec - start_ts.tv_nsec);
    elapsed_gettimeofday_us = elapsed_gettimeofday_ns / 1e3;

    // Measure foo
    clock_gettime(CLOCK_MONOTONIC, &start_ts);
    for (int i = 0; i < NUM_CALLS; i++)
        foo();
    clock_gettime(CLOCK_MONOTONIC, &end_ts);
    elapsed_foo_ns = (end_ts.tv_sec - start_ts.tv_sec) * 1e9 + (end_ts.tv_nsec - start_ts.tv_nsec);
    elapsed_foo_us = elapsed_foo_ns / 1e3;

    printf("Time for %d calls to usleep(0):\t\t" BOLD "%.0f microseconds %.0f ns\n" RESET,
           NUM_CALLS, elapsed_usleep_us, elapsed_usleep_ns);
    printf("Time for %d calls to gettimeofday():\t\t" BOLD "%.0f microseconds\t %.0fns\n" RESET,
           NUM_CALLS, elapsed_gettimeofday_us, elapsed_gettimeofday_ns);
    printf("Time for %d calls to foo():\t\t\t" BOLD "%.0f microseconds\t%.0f ns\n\n" RESET,
           NUM_CALLS, elapsed_foo_us, elapsed_foo_ns);

    return 0;
}