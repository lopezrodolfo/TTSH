# Makefile

CC = gcc
CFLAGS = -Wall -g

all: ttsh siesta

ttsh: ttsh.o history_queue.o parse_args.o
	$(CC) $(CFLAGS) -o ttsh ttsh.o history_queue.o parse_args.o

ttsh.o: ttsh.c parse_args.h history_queue.h
	$(CC) $(CFLAGS) -c ttsh.c

history_queue.o: history_queue.c history_queue.h
	$(CC) $(CFLAGS) -c history_queue.c

parse_args.o: parse_args.c parse_args.h
	$(CC) $(CFLAGS) -c parse_args.c

siesta: siesta.o
	$(CC) $(CFLAGS) -o siesta siesta.o

siesta.o: siesta.c
	$(CC) $(CFLAGS) -c siesta.c

clean:
	rm -f ttsh siesta *.o

.PHONY: all clean
