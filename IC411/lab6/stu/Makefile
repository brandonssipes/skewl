## IC 411 Fall 2018
## Makefile for Lab 6

TARGETS=detect midnite
FILES=detect.c midnight.c

CFLAGS= -Wall -Wextra -Wno-sign-compare -ggdb -fmax-errors=3 -O2 
LDFLAGS=-lpthread

# Default target
#all: $(TARGETS)

#$(TARGETS): $(OBJECTS)
#	$(CC) $(CFLAGS) $(FILES) -o $@ $(LDFLAGS)


midnite:
	$(CC) $(CFLAGS) -o $@ $@.c $(LDFLAGS)

detect: 
	$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS)

