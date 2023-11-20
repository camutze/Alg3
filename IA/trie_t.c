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

/*Retorna 1 se existe pelo menos um acento, 0 caso contrario*/
int word_tem_acento(const char *str)
{
    const char *accentedChars = "ÀÁÂÃÄÅÇÈÉÊËÌÍÎÏÒÓÔÕÖÙÚÛÜÝàáâãäåçèéêëìíîïðòóôõöùúûüýÿ�";

    for (size_t i = 0; i < strlen(str); ++i)
    {
        if (strchr(accentedChars, str[i]) != NULL)
        {
            return 1;
        }
    }

    return 0;
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

char *strdup_funcionando(const char *s) {
    size_t len = strlen(s) + 1;
    char *dup = malloc(len);
    if (dup != NULL) {
        memcpy(dup, s, len);
    }
    return dup;
}

/********************ARVORE***********************/
trie_node *criar_no(void)
{
    trie_node *novo_no; 

    if (!(novo_no = malloc(sizeof(trie_node))))
        tratar_erro("ERRO AO ALOCAR MEMORIA");


    for (int i = 0; i < ALPHA; i++)
        novo_no->filhos[i] = NULL;
    
    novo_no->fim_de_palavra = 0;
    return novo_no;
}

int trie_inserir(struct trie_node *raiz, const char *chave, const char *origem)
{
    trie_node *atual;
    int comprimento;;
    int indice;

    if(!raiz)
        return 0;

    atual = raiz;
    comprimento = strlen(chave);

    for (int i = 0; i < comprimento; i++)
    {
        indice = chave[i] - 'a';
        if (!atual->filhos[indice])
        {
            atual->filhos[indice] = criar_no();
            atual->filhos[indice]->origem = strdup_funcionando(origem);
        }
        atual = atual->filhos[indice];
    }

    if(strcmp(atual->origem, origem))
        atual->origem = strdup_funcionando(origem);
    
    atual->fim_de_palavra = 1;
    return 1;
}

void trie_destruir(trie_node *raiz)
{
    if (!raiz)
        return;

    for (int i = 0; i < ALPHA; i++)
        trie_destruir(raiz->filhos[i]);

    free(raiz->origem); 
    free(raiz);
}
