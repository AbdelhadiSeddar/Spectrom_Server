
CC=gcc

all: main

main: main.c
	if [ ! -d "bin" ]; then mkdir bin; fi && $(CC) *.c */*.c -o bin/Spectrom_Server.run -lpthread -lncurses

gdb: main.c
	if [ ! -d "bin" ]; then mkdir bin; fi && $(CC) *.c */*.c -g -o bin/Spectrom_Server[DEBUG].run -lpthread -lncurses
