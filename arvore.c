#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

arvore *cria_arvore()
{
    arvore *ipe;
    if (!(ipe = malloc(sizeof(arvore))))
        return 0;
    ipe->raiz = NULL;
    return ipe;
}
nodo *cria_nodo(int dado)
{
    nodo *filho;
    if (!(malloc(sizeof(arvore))))
        return 0;
    filho->dado = dado;
    filho->dir = NULL;
    filho->esq = NULL;

    return filho;
}
nodo *busca(arvore *ipe, int dado)
{
    // caso base, testa se ta vazio
    if (ipe->raiz == NULL)
        return 0;

    // se encontrou dado, retorna endereço
    if (dado == ipe->raiz->dado)
        return ipe->raiz->dado;

    // se dado for menor, busca do lado esquerdo
    if (dado < ipe->raiz->dado)
        return busca(ipe->raiz->esq, dado);

    // busca do lado direito
    return busca(ipe->raiz->dir, dado);
}
void imprime(arvore *ipe)
{
    if (ipe->raiz == NULL)
    {
        printf("Lista vazia\n");
        return;
    }

    imprime(ipe->raiz->esq);

    printf("%d, ", ipe->raiz->dado);

    imprime(ipe->raiz->dir);
}

int insere(arvore *ipe, int dado)
{
    //se null, cria novo nodo e insere dado
    if(ipe->raiz == NULL)
    {
        nodo *novo_f;
        if(!(novo_f = cria_nodo(dado)))
            return 0;
        
        ipe->raiz->esq = novo_f;
    }
    //se dado ja existe, retorna 1.
    else if(ipe->raiz->dado == dado)
        return 1;
    //se novo dado for menor que dado ja existente, insere para a esquerda, recursivamente.
    else if( dado < ipe->raiz->dado)
        return insere(ipe->raiz->esq, dado);
    // mesma coisa, pra direita
    return insere(ipe->raiz->dir, dado);
}

int remove(arvore *ipe, int dado)
{
    // if(ipe->raiz == NULL)
    //     return 0;
    // else if(ipe->raiz->esq == NULL && ipe->raiz->dir == NULL && ipe->raiz->dado == dado)
    //     free(ipe->raiz);
    // else if()
}