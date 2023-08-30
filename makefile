# Makefile para compilar arvore.h, arvore.c e main.c

CFLAGS = -Wall # flags de compilacao
CC = gcc

all: main.o arvore.o
	$(CC) -o programa main.o arvore.o

arvore.o: arvore.c arvore.h
	$(CC) -c $(CFLAGS) arvore.c

main.o: main.c arvore.h
	$(CC) -c $(CFLAGS) main.c

clean:
	rm -f *.o programa
