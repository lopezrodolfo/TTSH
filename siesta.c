// siesta.c
// Simple program that sleeps for a specified number of seconds

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * Main function for siesta program.
 * Sleeps for the specified number of seconds.
 *
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 * @return Exit status.
 */
int main(int argc, char *argv[]) {
    int sleep_time = 5; // default sleep time in seconds

    if (argc > 1) {
        sleep_time = atoi(argv[1]);
        if (sleep_time < 0) {
            fprintf(stderr, "Invalid sleep time.\n");
            return EXIT_FAILURE;
        }
    }

    printf("Siesta starting, will sleep for %d seconds...\n", sleep_time);
    sleep(sleep_time);
    printf("Siesta finished sleeping.\n");

    return EXIT_SUCCESS;
}
