CC=gcc
CFLAGS=-Wall -g

allocator: main.o allocator.o list.o
	$(CC) $(CFLAGS) -o allocator main.o allocator.o list.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c
	
allocator.o: allocator.c allocator.h
	$(CC) $(CFLAGS) -c allocator.c
	
list.o: list.c list.h	
	$(CC) $(CFLAGS) -c list.c
clean:
	rm -rf *.o
	rm -rf allocator