// history_queue.h
// Header file for the command history queue

#ifndef HISTORY_QUEUE_H
#define HISTORY_QUEUE_H

#define MAXHIST 10

/**
 * Struct to represent a history item.
 */
typedef struct {
    unsigned int cmd_id;  // Unique command ID
    char *cmd_line;       // Command line string
} history_item_t;

/**
 * Initializes the history queue.
 */
void init_history();

/**
 * Adds a command line to the history queue.
 *
 * @param cmd_line The command line string to add.
 */
void add_history(const char *cmd_line);

/**
 * Prints the history queue from oldest to most recent.
 */
void print_history();

/**
 * Frees the memory allocated for the history queue.
 */
void free_history();

#endif // HISTORY_QUEUE_H
