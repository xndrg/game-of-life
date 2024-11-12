CFLAGS=-Wall -Wextra -pedantic -ggdb -std=c11

main: main.c
	$(CC) $(CFLAGS) main.c -o main
run: main
	./main
