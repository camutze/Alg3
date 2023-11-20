CC      = gcc
CFLAGS  = -Wall -Wextra -g -std=c99 -pedantic
MAIN    =  main
ENTREGA = $(MAIN)-entrega

# programa principal
$(MAIN):   $(MAIN).o main.o trie_t.o
$(MAIN).o: $(MAIN).c trie_t.h


# TADs
trie_t.o: trie_t.c trie_t.h


clean:
	rm -f *.o *~ $(MAIN) $(ENTREGA) $(ENTREGA).tgz
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