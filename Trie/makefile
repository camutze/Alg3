CC=gcc
CFLAGS=-I.

DEPS = lib_trie.h
OBJ_LIB = lib_trie.o
OBJ_INSERE = insere.o
OBJ_PROCURA = procura.o
ENTREGA = backup

all: insere procura

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

insere: $(OBJ_INSERE) $(OBJ_LIB)
	$(CC) -o insere $(OBJ_INSERE) $(OBJ_LIB)

procura: $(OBJ_PROCURA) $(OBJ_LIB)
	$(CC) -o procura $(OBJ_PROCURA) $(OBJ_LIB)

clean:
	rm -f *.o *~ insere procura

cc:
	make clean ; reset ; make

push:
	make clean; git add . ; git commit -m "Makefile automático" ; git push

entrega: clean
	mkdir $(ENTREGA)
	cp *.c *.h makefile $(ENTREGA)
	rm *.o 
	chmod 600 $(ENTREGA)/*
	tar czvf $(ENTREGA).tgz $(ENTREGA)
	rm -rf $(ENTREGA)
	@echo "Arquivo $(ENTREGA).tgz criado para entrega"