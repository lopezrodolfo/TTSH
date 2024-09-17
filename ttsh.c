// ttsh.c
// Tiny Torero Shell
// Author: Rodolfo Lopez
// November 29, 2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

#include "parse_args.h"
#include "history_queue.h"

#define MAXLINE 1024

/**
 * Signal handler for SIGCHLD.
 * Reaps all terminated child processes to prevent zombies.
 *
 * @param sig Signal number (unused).
 */
void sigchld_handler(int sig);

/**
 * Runs the command specified by argv.
 * If background is non-zero, the command is run in the background.
 * Otherwise, the shell waits for the command to finish.
 *
 * @param argv Argument vector for the command to run.
 * @param background Non-zero if the command is to be run in background.
 */
void run_command(char **argv, int background);

int main(int argc, char *argv[]) {
    char line[MAXLINE];
    char *args[MAXARGS];
    int arg_count;
    int background;
    pid_t pid;

    // Initialize history
    init_history();

    // Register signal handler for SIGCHLD
    struct sigaction sa;
    sa.sa_handler = sigchld_handler;
    sa.sa_flags = SA_NOCLDSTOP;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Print prompt
        printf("ttsh> ");
        fflush(stdout);

        // Read input line
        if (fgets(line, MAXLINE, stdin) == NULL) {
            break; // EOF or error
        }

        // Remove trailing newline character
        line[strcspn(line, "\n")] = '\0';

        // Skip empty lines
        if (line[0] == '\0') {
            continue;
        }

        // Add to history
        add_history(line);

        // Parse arguments
        arg_count = parseArguments(line, args);
        if (arg_count == 0) {
            continue; // Empty command
        }

        // Check for built-in commands
        if (strcmp(args[0], "exit") == 0) {
            // Free history memory
            free_history();
            printf("Goodbye!\n");
            exit(EXIT_SUCCESS);
        } else if (strcmp(args[0], "history") == 0) {
            print_history();
            continue;
        }

        // Check if command is to be run in background
        background = 0;
        if (strcmp(args[arg_count - 1], "&") == 0) {
            background = 1;
            args[arg_count - 1] = NULL; // Remove '&' from arguments
        }

        // Run the command
        run_command(args, background);
    }

    // Free history memory
    free_history();

    return 0;
}

void sigchld_handler(int sig) {
    // Reap all terminated child processes
    int saved_errno = errno; // Save errno to avoid clobbering
    pid_t pid;
    int status;

    // Loop to reap all terminated children
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        // Optionally, you can print message about reaping child
        // printf("Child %d terminated\n", pid);
    }

    errno = saved_errno; // Restore errno
}

void run_command(char **argv, int background) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process

        // Restore default SIGINT handling
        struct sigaction sa;
        sa.sa_handler = SIG_DFL;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        sigaction(SIGINT, &sa, NULL);

        // Execute command
        if (execvp(argv[0], argv) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else if (pid > 0) {
        // Parent process
        if (!background) {
            // Wait for child to finish
            do {
                pid_t wpid = waitpid(pid, &status, WUNTRACED);
                if (wpid == -1) {
                    perror("waitpid");
                    break;
                }
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        } else {
            // Background process, do not wait
            printf("Started background process PID %d\n", pid);
        }
    } else {
        // Fork failed
        perror("fork");
    }
}
