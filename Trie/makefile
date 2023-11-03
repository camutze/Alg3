CC      = gcc
CFLAGS  = -Wall -Wextra -g -std=c99 -pedantic
MAIN    =  main
ENTREGA = $(MAIN)-entrega
TESTES  = testa-lef

# programa principal
$(MAIN):   $(MAIN).o main.o arquivo.o
$(MAIN).o: $(MAIN).c arquivo.h


# TADs
arquivo.o: arquivo.c arquivo.h


clean:
	rm -f *.o *~ $(MAIN) $(ENTREGA) $(ENTREGA).tgz
remake:
	make clean ; reset ; make

entrega: clean
	mkdir $(ENTREGA)
	cp *.c *.h makefile $(ENTREGA)
	rm -f $(ENTREGA)/testa*
	chmod 600 $(ENTREGA)/*
	tar czvf $(ENTREGA).tgz $(ENTREGA)
	rm -rf $(ENTREGA)
	@echo "Arquivo $(ENTREGA).tgz criado para entrega"