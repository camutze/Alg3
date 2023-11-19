#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#include "trie_t.h"
void tratar_erro(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

trie_node *criar_no(void)
{
    trie_node *novo_no = (trie_node *)malloc(sizeof(trie_node));
    if (novo_no)
    {
        novo_no->is_end = 0;
        for (int i = 0; i < TAMANHO_ALFABETO; i++)
        {
            novo_no->filhos[i] = NULL;
        }
    }

    return novo_no;
}

void trie_inserir(trie_node *raiz, const char *chave)
{
    int comprimento = strlen(chave);
    trie_node *atual = raiz;

    for (int i = 0; i < comprimento; i++)
    {
        int indice = chave[i] - 'a';
        if (!atual->filhos[indice])
        {
            atual->filhos[indice] = criar_no();
        }
        atual = atual->filhos[indice];
    }

    atual->is_end = 1;
}

int trie_busca(trie_node *raiz, const char *chave)
{
    int comprimento = strlen(chave);
    trie_node *atual = raiz;

    for (int i = 0; i < comprimento; i++)
    {
        int indice = chave[i] - 'a';

        if (!atual->filhos[indice])
        {
            return 0;
        }
        atual = atual->filhos[indice];
    }

    return (atual != NULL && atual->is_end);
}

void trie_imprime_prefixo(trie_node *raiz, const char *prefixo)
{
    int comprimento = strlen(prefixo);
    trie_node *atual = raiz;

    for (int i = 0; i < comprimento; i++)
    {
        int indice = prefixo[i] - 'a';
        if (!atual->filhos[indice])
        {
            printf("No words found with the given prefix.\n");
            return;
        }
        atual = atual->filhos[indice];
    }

    trie_imprime(atual);
}

void trie_imprime(trie_node *raiz)
{
    if (raiz)
    {
        for (int i = 0; i < TAMANHO_ALFABETO; i++)
        {
            if (raiz->filhos[i])
            {
                char c = 'a' + i;
                printf("%c", c);
                trie_imprime(raiz->filhos[i]);
            }
        }
        if (raiz->is_end)
        {
            printf("\n");
        }
    }
}

void trie_destruir(trie_node *raiz)
{
    if (raiz)
    {
        for (int i = 0; i < TAMANHO_ALFABETO; i++)
        {
           trie_destruir(raiz->filhos[i]);
        }
        free(raiz);
    }
}

/*Retorna 0 se existe pelo menos um acento, 1 caso contrario*/
int word_acento(char *str)
{
    char *com_acentos = "áàâãéèêíìîóòôõúùûçÁÀÂÃÉÈÊÍÌÎÓÒÔÕÚÙÛÇ";

    for (int i = 0; str[i] != '\0'; ++i)
        for (int j = 0; com_acentos[j] != '\0'; j++)
            if (str[i] == com_acentos[j])
                return 0;
    return 1;
}

void word_pontua(char *str)
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

void word_sem_minusc(char *str)
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