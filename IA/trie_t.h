#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHA (26)

typedef struct trie_node
{
    struct trie_node *filhos[ALPHA];
    int fim_de_palavra;
    char *origem;
}trie_node;

void tratar_erro(const char *msg);

int word_tem_acento(const char *str);

void word_pontua(char *str);

void word_sem_minusc(char *str);

/***********EVENTOS****************/

trie_node *criar_no(void);

int trie_inserir(struct trie_node *raiz, const char *chave, const char *origem);

void trie_destruir(trie_node *raiz);


#endif



