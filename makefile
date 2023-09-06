
CC=clang

all: main

main: main.c
	if [ ! -d "bin" ]; then mkdir bin; fi && $(CC) *.c */*.c */*/*.c -o bin/Spectrom_Server.run -lpthread -lncurses

gdb: main.c
	if [ ! -d "bin" ]; then mkdir bin; fi && $(CC) *.c */*.c */*/*.c -g -o bin/Spectrom_Server[DEBUG].run -lpthread -lncurses

san: main.c
	if [ ! -d "bin" ]; then mkdir bin; fi && $(CC) *.c */*.c */*/*.c -fsanitize=address -g  -o bin/Spectrom_Server[SANITIZED].run -lpthread -lncurses

clean:
	if [ -d "bin" ]; then rm -rf bin/*;