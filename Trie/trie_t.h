#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_ALFABETO 26
#define N_MAX_ARQUIVOS 14 //numero maximo de arquivos que podem ser lidos

typedef struct tree_trie
{
    struct trie_node **raiz;
} tree_trie;

typedef struct trie_node
{
    struct trie_node *filhos[TAMANHO_ALFABETO];
    char **origem[N_MAX_ARQUIVOS];
    int is_end;
} trie_node;

/* Finaliza execucao e imprime a mensagem
 que foi passada como parametro*/
void tratar_erro(const char *msg);

/* Cria um novo no da trie e retorna o ponteiro para ele */
trie_node *criar_no(void);

/* Insere uma nova chave na trie */
void trie_inserir(trie_node *raiz, const char *chave);

/* Busca uma chave na trie */
int trie_busca(trie_node *raiz, const char *chave);


void trie_imprime_prefixo(trie_node *raiz, const char *prefixo);

void trie_imprime(trie_node *raiz);

void trie_destruir(trie_node *raiz);

int word_acento(char *str);

void word_pontua(char *str);

void word_sem_minusc(char *str);


#endif



