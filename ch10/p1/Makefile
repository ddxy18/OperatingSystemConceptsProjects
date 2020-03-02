CC=gcc
CFLAGS=-Wall -g

manager: main.o virtual_memory_manager.o page_table.o TLB.o physical_memory.o free_list.o FIFO_replacement.o
	$(CC) $(CFLAGS) -o manager main.o virtual_memory_manager.o page_table.o TLB.o physical_memory.o free_list.o FIFO_replacement.o

main.o: main.c virtual_memory_manager.h
	$(CC) $(CFLAGS) -c main.c
	
virtual_memory_manager.o: virtual_memory_manager.c virtual_memory_manager.h physical_memory.h page_table.h TLB.h free_list.h FIFO_replacement.h
	$(CC) $(CFLAGS) -c virtual_memory_manager.c
	
page_table.o: page_table.c page_table.h
	$(CC) $(CFLAGS) -c page_table.c

TLB.o: TLB.c TLB.h
	$(CC) $(CFLAGS) -c TLB.c

physical_memory.o: physical_memory.c physical_memory.h
	$(CC) $(CFLAGS) -c physical_memory.c

free_list.o: free_list.c free_list.h physical_memory.h
	$(CC) $(CFLAGS) -c free_list.c

FIFO_replacement.o: FIFO_replacement.c FIFO_replacement.h
	$(CC) $(CFLAGS) -c FIFO_replacement.c

clean:
	rm -rf *.o
	rm -rf manager
	rm -rf test.txt