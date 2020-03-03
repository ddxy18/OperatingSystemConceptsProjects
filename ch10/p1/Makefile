CC=gcc
CFLAGS=-Wall -g

FIFO_manager: main.o virtual_memory_manager.o FIFO_replacement.o TLB.o physical_memory.o free_list.o
	$(CC) $(CFLAGS) -o FIFO_manager main.o virtual_memory_manager.o FIFO_replacement.o TLB.o physical_memory.o free_list.o

LRU_manager: main.o virtual_memory_manager.o LRU_replacement.o TLB.o physical_memory.o free_list.o
	$(CC) $(CFLAGS) -o LRU_manager main.o virtual_memory_manager.o LRU_replacement.o TLB.o physical_memory.o free_list.o

main.o: main.c virtual_memory_manager.h
	$(CC) $(CFLAGS) -c main.c
	
virtual_memory_manager.o: virtual_memory_manager.c virtual_memory_manager.h page_replacement.h physical_memory.h page_table.h TLB.h free_list.h
	$(CC) $(CFLAGS) -c virtual_memory_manager.c

FIFO_replacement.o: FIFO_replacement.c FIFO_replacement.h page_replacement.h
	$(CC) $(CFLAGS) -c FIFO_replacement.c

LRU_replacement.o: LRU_replacement.c LRU_replacement.h page_replacement.h
	$(CC) $(CFLAGS) -c LRU_replacement.c

TLB.o: TLB.c TLB.h
	$(CC) $(CFLAGS) -c TLB.c

physical_memory.o: physical_memory.c physical_memory.h
	$(CC) $(CFLAGS) -c physical_memory.c

free_list.o: free_list.c free_list.h physical_memory.h
	$(CC) $(CFLAGS) -c free_list.c

clean:
	rm -rf *.o
	rm -rf FIFO_manager
	rm -rf LRU_manager
	rm -rf test.txt