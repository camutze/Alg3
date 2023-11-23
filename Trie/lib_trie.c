#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "lib_trie.h"

TrieNode *cria_nodo_trie()
{
    TrieNode *node;
    /*se não alocar sai*/
    if (!(node = malloc(sizeof(TrieNode))))
        exit(1);
    /*Se é final de palavra 1, 0 caso contrario*/
    node->eh_final = 0;
    /*inicializa todos os filhos como NULL*/
    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->filhos[i] = NULL;
    return node;
}

void inserir_trie(TrieNode *raiz, const char *palavra, const char *origem)
{
    int index;
    TrieNode *percorre = raiz;
    /*percorre a palavra para inserir*/
    while (*palavra != '\0')
    {
        index = *palavra - 'a';
        if (percorre->filhos[index] == NULL)
        {
            percorre->filhos[index] = cria_nodo_trie();
            strcpy(percorre->filhos[index]->origem, origem); // Copia a origem para o novo nó
        }
        /*vai para o proximo nivel*/
        percorre = percorre->filhos[index];
        palavra++;
    }
    percorre->eh_final = 1;
}

void print_trie(TrieNode *raiz, char str[], int nivel)
{   
    /*se for final de palavra imprime*/
    if (raiz->eh_final)
    {
        str[nivel] = '\0';
        printf("%s ", str);
        printf("%s\n", raiz->origem);
    }
    /*percorre todos os filhos*/
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (raiz->filhos[i])
        {
            str[nivel] = i + 'a';
            print_trie(raiz->filhos[i], str, nivel + 1);
        }
    }
}

void print_prefix(TrieNode *raiz, const char *prefix)
{   
    /*nodo que vai percorrer*/
    TrieNode *percorre = raiz;

    printf("Palavras com prefixo %s:\n", prefix);
    /*percorre o prefixo, e apartir dai chama o imprime*/
    while (*prefix != '\0')
    {
        int index = *prefix - 'a';
        if (!percorre->filhos[index])
            return;
        percorre = percorre->filhos[index];
        prefix++;
    }

    char str[TAM_PALAVRA];
    print_trie(percorre, str, 0);
}

void destroi(TrieNode *raiz)
{   
    /*destroid todos os filhos do vetor, recursivamente*/
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (raiz->filhos[i] != NULL)
            destroi(raiz->filhos[i]);
    free(raiz);
}

int tem_acento(char *str)
{
    char *acentuadas = "ÀÁÂÃÄÅÇÈÉÊËÌÍÎÏÒÓÔÕÖÙÚÛÜÝàáâãäåçèéêëìíîïðòóôõöùúûüýÿ";
    size_t i, j;
    /*percorre a string e compara com as letras acentuadas*/
    for (i = 0; i < strlen(str); i++)
    {
        for (j = 0; j < strlen(acentuadas); j++)
        {
            if (str[i] == acentuadas[j])
            {
                /* Retorna 1 se encontrar um acento a ser ignorado */
                return 1; 
            }
        }
    }
    /* Retorna 0 se não encontrar um acento a ser ignorado */
    return 0;
}

void retira_pontuacao(char *str)
{
    int len = strlen(str);
    int j = 0;
    for (int i = 0; i < len; i++)
    {  
         /*se não for pontuação copia*/
        if (!ispunct(str[i]))
        {
            str[j++] = str[i];
        }
    }
    /*coloca o fim da string*/
    str[j] = '\0';
}

void tudo_minusculo(char *str)
{
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        /*se for maiusculo converte para minusculo*/
        if (isupper(str[i]))
        {
            str[i] = tolower(str[i]); // converte para minuscula
        }
    }
}

void export_trie(FILE *base, TrieNode *raiz)
{
    /*escreve o nodo no arquivo*/
    fwrite(raiz, sizeof(TrieNode), 1, base);
    /*percorre todos os filhos*/
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (raiz->filhos[i])
        {   
            /*chama recursivamente para cada filho*/
            export_trie(base, raiz->filhos[i]);
        }
    }
}

TrieNode *import_trie(FILE *base)
{
    TrieNode *raiz;

    if(!(raiz = malloc(sizeof(TrieNode))))
        exit(1);

    /*l faz a leitura de um elemento de tamanho nodo da arvore 
    e coloca no nodo raiz*/
    if (fread(raiz, sizeof(TrieNode), 1, base) != 1)
    {
        free(raiz);
        return NULL;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (raiz->filhos[i])
        {
            /*chama recursivamente para cada filho*/
            raiz->filhos[i] = import_trie(base);
        }
    }
    return raiz;
}