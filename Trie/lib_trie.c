#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "lib_trie.h"

TrieNode *get_node()
{
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    node->is_end_of_word = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;
    return node;
}

void insert(TrieNode *root, const char *word, const char *origem)
{
    int index;
    TrieNode *pCrawl = root;
    while (*word != '\0')
    {
        index = *word - 'a';
        if (pCrawl->children[index] == NULL)
        {
            pCrawl->children[index] = get_node();
            strcpy(pCrawl->children[index]->origem, origem); // Copia a origem para o novo nó
        }
        pCrawl = pCrawl->children[index];
        word++;
    }
    pCrawl->is_end_of_word = 1;
}

void print_trie(TrieNode *root, char str[], int level)
{
    if (root->is_end_of_word)
    {
        str[level] = '\0';
        printf("%s ", str);
        printf("%s\n", root->origem);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {
            str[level] = i + 'a';
            print_trie(root->children[i], str, level + 1);
        }
    }
}

void print_prefix(TrieNode *root, const char *prefix)
{
    printf("Palavras com prefixo %s:\n", prefix);
    TrieNode *pCrawl = root;
    while (*prefix != '\0')
    {
        int index = *prefix - 'a';
        if (!pCrawl->children[index])
            return;
        pCrawl = pCrawl->children[index];
        prefix++;
    }

    char str[TAM_PALAVRA];
    print_trie(pCrawl, str, 0);
}

void destroy(TrieNode *root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i] != NULL)
            destroy(root->children[i]);
    free(root);
}

int tem_acento(char *str)
{
    char *acentuadas = "ÀÁÂÃÄÅÇÈÉÊËÌÍÎÏÒÓÔÕÖÙÚÛÜÝàáâãäåçèéêëìíîïðòóôõöùúûüýÿ";
    size_t i, j;

    for (i = 0; i < strlen(str); i++)
    {
        for (j = 0; j < strlen(acentuadas); j++)
        {
            if (str[i] == acentuadas[j])
            {
                return 1; // Retorna 1 se encontrar um acento a ser ignorado
            }
        }
    }
    return 0; // Retorna 0 se não encontrar acentos a serem ignorados
}

void retira_pontuacao(char *str)
{
    int len = strlen(str);
    int j = 0;
    for (int i = 0; i < len; i++)
    {
        if (!ispunct(str[i]))
        {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

void tudo_minusculo(char *str)
{
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (isupper(str[i]))
        {
            str[i] = tolower(str[i]); // converte para minuscula
        }
    }
}

void export_trie(FILE *base, TrieNode *root, char str[], int level)
{
    if (root->is_end_of_word)
    {
        str[level] = '\0';
        fprintf(base, "%s ", str);
        fprintf(base, "%s\n", root->origem);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {
            str[level] = i + 'a';
            export_trie(base, root->children[i], str, level + 1);
        }
    }
}

void import_trie(FILE *base, TrieNode *root)
{
    char word[TAM_PALAVRA];
    char origem[TAM_ARQUIVO];

    // Verifica se o arquivo está vazio
    fseek(base, 0, SEEK_END);
    if (!ftell(base))
        return;

    rewind(base); // Volta ao início do arquivo

    while (fscanf(base, "%s %s", word, origem) == 2)
    {
        insert(root, word, origem);
    }
}
