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

    if (!(filho = malloc(sizeof(arvore))))
        return 0;
    filho->dado = dado;
    filho->dir = NULL;
    filho->esq = NULL;

    return filho;
}
nodo *busca(nodo *pai, int dado)
{
    // caso base, testa se ta vazio
    if (pai == NULL)
        return 0;

    // se encontrou dado, retorna endereço
    if (dado == pai->dado)
        return pai;

    // se dado for menor, busca do lado esquerdo
    if (dado < pai->dado)
        return busca(pai->esq, dado);

    // busca do lado direito
    return busca(pai->dir, dado);
}
void imprime(nodo *pai)
{
    if (pai == NULL)
    {
        printf("Lista vazia\n");
        return;
    }

    imprime(pai->esq);

    printf("%d, ", pai->dado);

    imprime(pai->dir);
}

int insere(nodo *pai, int dado)
{
    // se null, cria novo nodo e insere dado
    if (pai == NULL)
    {
        nodo *novo_f;
        if (!(novo_f = cria_nodo(dado)))
            return 0;

        pai->esq = novo_f;
    }
    // se dado ja existe, retorna 1.
    else if (pai->dado == dado)
        return 1;
    // se novo dado for menor que dado ja existente, insere para a esquerda, recursivamente.
    else if (dado < pai->dado)
        return insere(pai->esq, dado);
    // mesma coisa, pra direita
    return insere(pai->dir, dado);
}

int remover(nodo *pai, int dado)
{
    if (!pai)
        return 0;
    if(pai->dado == dado)

    if(!pai->esq)
        return remover(pai->dir, dado);
    return 0;
}