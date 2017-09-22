all:
	gcc lib/*.c test.c -Iinclude/ -O3 -W -Wall -o test
