#include <stdio.h>
#include <stdlib.h>
#include "avl-tree.h"

arvore *cria_arvore()
{
    arvore *avl;

    if (!(avl = malloc(sizeof(arvore))))
        return 0;
    avl->raiz = NULL;
    return avl;
}
nodo *cria_nodo(int r)
{
    nodo *filho;

    if (!(filho = malloc(sizeof(arvore))))
        return 0;
    filho->r = r;
    filho->dir = NULL;
    filho->esq = NULL;

    return filho;
}
nodo *busca(nodo *no, int r)
{
    // caso base, testa se ta vazio
    if (!no)
        return 0;

    // se encontrou r, retorna endereço
    if (r == no->r)
        return no;

    // se r for menor, busca do lado esquerdo
    if (r < no->r)
        return busca(no->esq, r);

    // busca do lado direito
    return busca(no->dir, r);
}

void imprime(nodo *no)
{
    if (!no)
        return;

    imprime(no->esq);
    printf("(%d)", no->r);
    imprime(no->dir);
}

int insere(nodo *no, int r)
{
    return 0;
}

nodo *rotacao_esq(nodo *no)
{
    if (!no)
        return 0;
    no->dir->dir = no; // neto esquerdo aponta para o pai
    no->dir = NULL;    // pai aponta para NULL
    return no->esq;
}

int rotacao_dir(nodo *no)
{
    return 0;
}

int remover(nodo *no, int r)
{
    return 0;
}

void destruir_arvore(nodo *no)
{
    if (!no)
        return;
    if (no->dir)
        destruir_arvore(no->dir);
    if (no->esq)
        destruir_arvore(no->esq);

    free(no);

    return;
}