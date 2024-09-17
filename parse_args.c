// parse_args.c
// Implementation of the parseArguments function

#include <string.h>
#include "parse_args.h"

/**
 * Parses the command line into an argv array.
 *
 * @param line The command line string to parse.
 * @param argv The array to store the arguments.
 * @return The number of arguments parsed.
 */
int parseArguments(char *line, char **argv) {
    int argc = 0;
    char *token;

    // Use strtok to split the line into tokens
    token = strtok(line, " \t\n");
    while (token != NULL && argc < MAXARGS - 1) {
        argv[argc++] = token;
        token = strtok(NULL, " \t\n");
    }
    argv[argc] = NULL;
    return argc;
}
