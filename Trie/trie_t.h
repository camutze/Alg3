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

void inserir(trie_node *raiz, const char *chave);

int buscar(trie_node *raiz, const char *chave);

void imprime_prefixo(trie_node *raiz, const char *prefixo);

void imprime(trie_node *raiz);

void destruir_trie(trie_node *raiz);

int tem_acento(char *str);

void remove_pontuacao(char *str);

void converte_minusculas(char *str);



#endif