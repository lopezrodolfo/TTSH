// parse_args.h
// Header file for parseArguments function

#ifndef PARSE_ARGS_H
#define PARSE_ARGS_H

#define MAXLINE 1024
#define MAXARGS 128

/**
 * Parses the command line into an argv array.
 *
 * @param line The command line string to parse.
 * @param argv The array to store the arguments.
 * @return The number of arguments parsed.
 */
int parseArguments(char *line, char **argv);

#endif // PARSE_ARGS_H
