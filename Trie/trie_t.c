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
TrieNode *criaNo()
{
    TrieNode *novoNo = NULL;
    novoNo = (TrieNode *)malloc(sizeof(TrieNode));
    if (novoNo)
    {
        int i;
        novoNo->fimDaPalavra = 0;
        novoNo->origemArquivo = NULL; // Inicializa o campo origemArquivo como NULL
        for (i = 0; i < ALFABETO; i++)
            novoNo->filhos[i] = NULL;
    }
    return novoNo;
}

// Insere uma palavra na Trie
void insere(TrieNode *raiz, const char *palavra, const char *origemArquivo)
{
    int nivel;
    int comprimento = strlen(palavra);
    int indice;
    TrieNode *p = raiz;
    for (nivel = 0; nivel < comprimento; nivel++)
    {
        indice = CHAR_TO_INDEX(palavra[nivel]);
        if (!p->filhos[indice])
            p->filhos[indice] = criaNo();
        p = p->filhos[indice];
    }
    p->fimDaPalavra = 1;
    p->origemArquivo = strdup(origemArquivo); // Armazena a origem do arquivo
}

// Retorna 1 se a palavra é encontrada na Trie, caso contrário retorna 0
int busca(TrieNode *raiz, const char *palavra)
{
    int nivel;
    int comprimento = strlen(palavra);
    int indice;
    TrieNode *p = raiz;
    for (nivel = 0; nivel < comprimento; nivel++)
    {
        indice = CHAR_TO_INDEX(palavra[nivel]);
        if (!p->filhos[indice])
            return 0;
        p = p->filhos[indice];
    }
    if (p != NULL && p->fimDaPalavra)
    {
        printf("Origem do arquivo: %s\n", p->origemArquivo); // Imprime a origem do arquivo
        return 1;
    }
    return 0;
}

// Libera a memória alocada para a Trie
void destroi(TrieNode *no)
{
    int i;
    for (i = 0; i < ALFABETO; i++)
        if (no->filhos[i])
            destroi(no->filhos[i]);
    free(no->origemArquivo); // Libera a memória alocada para origemArquivo
    free(no);
}
