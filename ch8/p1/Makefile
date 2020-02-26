CC=gcc
CFLAGS=-Wall -g

main: main.o banker.o
	$(CC) $(CFLAGS) -o main main.o banker.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c
	
banker.o: banker.c
	$(CC) $(CFLAGS) -c banker.c

clean:
	rm -rf *.o
	rm -rf main