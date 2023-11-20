#ifndef TRIE_T_H
#define TRIE_T_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALFABETO (26)                        // Tamanho do alfabeto (número de letras)
#define CHAR_TO_INDEX(c) ((int)c - (int)'a') // Converte caractere para índice

// Estrutura do nó da Trie
typedef struct TrieNode
{
    struct TrieNode *filhos[ALFABETO];
    int fimDaPalavra;
    char *origemArquivo; // Adicionado campo para armazenar a origem do arquivo
} TrieNode;

// Cria um novo nó da Trie
TrieNode *criaNo();

// Insere uma palavra na Trie
void insere(TrieNode *raiz, const char *palavra, const char *origemArquivo);

// Retorna 1 se a palavra é encontrada na Trie, caso contrário retorna 0
int busca(TrieNode *raiz, const char *palavra);

// Libera a memória alocada para a Trie
void destroi(TrieNode *no);

#endif
