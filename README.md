# Tiny Torero Shell (ttsh)

A simple Unix-like shell implementation in C.

## Author

Rodolfo Lopez

## Date

November 29, 2020

## Features

- Basic command execution
- Background process support
- Command history
- Built-in `exit` and `history` commands
- Signal handling for child processes

## Files

- `ttsh.c`: Main shell implementation
- `history_queue.c` & `history_queue.h`: Command history functionality
- `parse_args.c` & `parse_args.h`: Command line parsing
- `siesta.c`: Simple program for testing background processes
- `Makefile`: Build configuration

## Building

To compile the project, run:

```
make
```

This will create two executables: `ttsh` and `siesta`.

## Usage

Run the shell:

```
./ttsh
```

Use the `siesta` program to test background processes:

## Cleaning up

To remove compiled files:

```
make clean
```
