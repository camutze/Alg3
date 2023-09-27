# Makefile para compilar avl-tree.h, avl-tree.c e main.c

CFLAGS = -Wall # flags de compilacao
CC = gcc

all: main.o avl-tree.o
	$(CC) -o exec main.o avl-tree.o

avl-tree.o: avl-tree.c avl-tree.h
	$(CC) -c $(CFLAGS) avl-tree.c

main.o: main.c avl-tree.h
	$(CC) -c $(CFLAGS) main.c

clean:
	rm -f *.o exec
