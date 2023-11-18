#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_ALFABETO 26

typedef struct tree_trie
{
    struct trie_node **raiz;
} tree_trie;

typedef struct trie_node
{
    struct trie_node *filhos[TAMANHO_ALFABETO];
    int is_end;
} trie_node;

void tratar_erro(const char *msg);

trie_node *criar_no(void);

void trie_inserir(trie_node *raiz, const char *chave);

int trie_busca(trie_node *raiz, const char *chave);

void trie_imprime_prefixo(trie_node *raiz, const char *prefixo);

void trie_imprime(trie_node *raiz);

void trie_destruir(trie_node *raiz);

int word_acento(char *str);

void word_pontua(char *str);

void word_minusc(char *str);

#endif



