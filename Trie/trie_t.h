#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_ALFABETO 26

typedef struct trie_node
{
    struct trie_node *filhos[TAMANHO_ALFABETO];
    int is_end;
} trie_node;

void tratar_erro(const char *msg);

trie_node *criar_no(void);

void inserir(trie_node *raiz, const char *chave);

int buscar(trie_node *raiz, const char *chave);

int comeca_com(trie_node *raiz, const char *prefixo);

void destruir_trie(trie_node *raiz);

void imprime(trie_node *raiz);

#endif 
