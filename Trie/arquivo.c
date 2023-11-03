#include <stdlib.h>

#include "arquivo.h"

trie_t *cria_trie()
{
    trie_t *trie;
    if (!(trie = malloc(sizeof(trie_t))))
        return NULL;
    trie->raiz = cria_no();
    return trie;
}

void libera_trie(trie_t *trie)
{   
    if(!trie)
        return;
    if(!trie->raiz)
        return;

    libera_nodo(trie->raiz);
    free(trie);
}

nodo_t *cria_no()
{
    nodo_t *no;
    if (!(no = malloc(sizeof(nodo_t))))
        return NULL;
    no->fim = 0;
    for (int i = 0; i < ALFABETO; i++)
        no->filho[i] = NULL;
    return no;
}

void libera_no(nodo_t *no)
{
    if(!no)
        return;
    for (int i = 0; i < ALFABETO; i++)
        libera_no(no->filho[i]);
    free(no);
}

int insere_trie(trie_t *trie, char *palavra, int origem)
{
    if (!trie)
        return 0;
    if (!trie->raiz)
        return 0;
    if (!palavra)
        return 0;

    if (strlen(palavra) < MIN_PALAVRA)
        return 0;
    insere_nodo(trie->raiz, palavra, origem);
    return 1;
}

int insere_nodo(nodo_t *nodo, char *palavra, int origem)
{
    if (!nodo)
        return 0;
    if (!palavra)
        return 0;

    if (*palavra == '\0')
    {
        nodo->fim = 1;
        nodo->origem = origem;
        return 1;
    }
    int indice = indice_letra(*palavra);
    if (!nodo->filho[indice])
        nodo->filho[indice] = cria_no();
    return insere_nodo(nodo->filho[indice], palavra + 1, origem);
}

int insere_nodo(nodo_t *nodo, char *palavra, int origem)
{
    if (!nodo)
        return 0;
    if (!palavra)
        return 0;

    if (*palavra == '\0')
    {
        nodo->fim = 1;
        nodo->origem = origem;
        return 1;
    }
    int indice = indice_letra(*palavra);
    if (!nodo->filho[indice])
        nodo->filho[indice] = cria_no();
    return insere_nodo(nodo->filho[indice], palavra + 1, origem);
}

int indice_letra(char letra)
{
    if (letra >= 'a' && letra <= 'z')
        return letra - 'a';
    if (letra >= 'A' && letra <= 'Z')
        return letra - 'A' + 26;
    return -1;
}