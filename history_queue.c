// history_queue.c
// Implementation of the command history queue

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history_queue.h"

/* Static variables to keep track of the history */
static history_item_t history[MAXHIST];
static int hist_count = 0; // Total number of commands added
static int hist_start = 0; // Index of the oldest command
static int hist_size = 0;  // Current number of commands in history

/**
 * Initializes the history queue.
 */
void init_history() {
    for (int i = 0; i < MAXHIST; i++) {
        history[i].cmd_id = 0;
        history[i].cmd_line = NULL;
    }
}

/**
 * Adds a command line to the history queue.
 *
 * @param cmd_line The command line string to add.
 */
void add_history(const char *cmd_line) {
    if (cmd_line == NULL || cmd_line[0] == '\0')
        return; // Don't add empty lines

    // Increment the total command ID
    hist_count++;

    int index;
    if (hist_size < MAXHIST) {
        // Add new command
        index = (hist_start + hist_size) % MAXHIST;
        hist_size++;
    } else {
        // Overwrite the oldest command
        index = hist_start;
        free(history[index].cmd_line);
        hist_start = (hist_start + 1) % MAXHIST;
    }
    history[index].cmd_id = hist_count;
    history[index].cmd_line = strdup(cmd_line);
}

/**
 * Prints the history queue from oldest to most recent.
 */
void print_history() {
    int index, i;
    for (i = 0; i < hist_size; i++) {
        index = (hist_start + i) % MAXHIST;
        printf("%u %s\n", history[index].cmd_id, history[index].cmd_line);
    }
}

/**
 * Frees the memory allocated for the history queue.
 */
void free_history() {
    int index, i;
    for (i = 0; i < hist_size; i++) {
        index = (hist_start + i) % MAXHIST;
        free(history[index].cmd_line);
    }
}
