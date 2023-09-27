#include <stdio.h>
#include <stdlib.h>
#include "avl-tree.h"

arvore *cria_arvore()
{
    arvore *avl;

    if (!(avl = malloc(sizeof(arvore))))
        return NULL;
    avl->raiz = NULL;

    return avl;
}
nodo *cria_nodo(int r)
{
    nodo *filho;

    if (!(filho = malloc(sizeof(struct nodo))))
        return NULL;

    filho->alt = 0;
    filho->r = r;
    filho->dir = NULL;
    filho->esq = NULL;

    return filho;
}
int busca(nodo *no, int r)
{
    // caso base, testa se ta vazio
    if (!no)
        return 0;

    if (r == no->r)
        return 1;
    /* se r for menor, busca do lado esquerdo*/
    if (r < no->r)
        return busca(no->esq, r);
    /* busca do lado direito*/
    return busca(no->dir, r);
}

void imprime(nodo *no)
{
    if (!no)
    {
        printf("()");
        return;
    }

    printf("(");
    printf("%d,", no->r);
    imprime(no->esq);
    printf(",");
    imprime(no->dir);
    printf(")");
}

nodo *procura_menor(nodo *atual)
{
    nodo *no1 = atual;
    nodo *no2 = atual->esq;

    while (no2)
    {
        no1 = no2;
        no2 = no2->esq;
    }

    return no1;
}

int insere_nodo(nodo **raiz, int r)
{
    if (!*raiz)
    {
        /* Caso onde encontrou uma folha para a inserção */
        *raiz = cria_nodo(r);
        return 1;
    }

    /* Calcula se a inserção vai ser à esquerda da árvore */
    if (r < (*raiz)->r)
    {
        /* Se a inserção funcionou, entra no if e testa o balanceamento */
        if (!insere_nodo(&(*raiz)->esq, r))
            return 0;

        if (fator_balanceamento(*raiz) >= 2)
        {
            if (r < (*raiz)->esq->r)
                rotacao_dir(raiz);
            else
                rotacao_dir_esq(raiz);
        }
        (*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)->dir)) + 1; // atualiza a altura do nó
        return 1;
    }

    /* Não foi à esquerda, testa se insiro à direita */
    else if (r > (*raiz)->r)
    {
        if (!insere_nodo(&(*raiz)->dir, r))
            return 0;

        if (fator_balanceamento(*raiz) >= 2)
        {
            if (r > (*raiz)->dir->r)
                rotacao_esq(raiz);
            else
                rotacao_esq_dir(raiz);
        }
        (*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)->dir)) + 1; // atualiza a altura do nó
        return 1;
    }
    return 0;
}

int remove_nodo(nodo **raiz, int r)
{
    if (!*raiz)
        return 0;

    int res; /* resultado da busca*/

    if (r < (*raiz)->r)
    {
        if ((res = remove_nodo(&(*raiz)->esq, r)))
        {
            if (fator_balanceamento(*raiz) >= 2)
            {
                if (alt_no((*raiz)->dir->esq) <= alt_no((*raiz)->dir->dir))
                    rotacao_dir(raiz);
                else
                    rotacao_esq_dir(raiz);
            }
        }
    }
    else if (r > (*raiz)->r)
    {
        if ((res = remove_nodo(&(*raiz)->dir, r)))
        {
            if (fator_balanceamento(*raiz) >= 2)
            {
                if (alt_no((*raiz)->esq->dir) <= alt_no((*raiz)->esq->esq))
                    rotacao_dir(raiz);
                else
                    rotacao_dir_esq(raiz);
            }
        }
    }
    else
    {
        nodo *no_aux;
        if (!(*raiz)->esq || !(*raiz)->dir)
        {
            no_aux = *raiz;
            if (!(*raiz)->esq)
                *raiz = (*raiz)->dir;
            else
                *raiz = (*raiz)->esq;
            free(no_aux);
        }
        else
        {
            no_aux = procura_menor((*raiz)->dir);
            (*raiz)->r = no_aux->r;
            remove_nodo(&(*raiz)->dir, no_aux->r);
            if (fator_balanceamento(*raiz) >= 2)
            {
                if (alt_no((*raiz)->esq->dir) <= alt_no((*raiz)->esq->esq))
                    rotacao_dir(raiz);
                else
                    rotacao_dir_esq(raiz);
            }
        }
        return 1;
    }
    return res;
}

int fator_balanceamento(nodo *no)
{
    if (!no)
        return 0;
    // nao precisa do sinal, pois o labs retorna o valor absoluto
    return abs(alt_no(no->esq) - alt_no(no->dir));
}
void rotacao_esq(nodo **raiz)
{
    nodo *no_aux;
    if (!raiz)
        return;

    no_aux = (*raiz)->dir;
    (*raiz)->dir = no_aux->esq;
    no_aux->esq = *raiz;

    (*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)->dir)) + 1;
    no_aux->alt = maior(alt_no(no_aux->esq), alt_no(no_aux->dir)) + 1;
    *raiz = no_aux;
}

void rotacao_dir(nodo **raiz)
{
    nodo *no_aux;
    if (!raiz)
        return;

    no_aux = (*raiz)->esq;

    (*raiz)->esq = no_aux->dir;
    no_aux->dir = *raiz;
    (*raiz)->alt = maior(alt_no((*raiz)->esq), alt_no((*raiz)->dir)) + 1;
    no_aux->alt = maior(alt_no(no_aux->esq), alt_no(no_aux->dir)) + 1;
    *raiz = no_aux;
}

void rotacao_esq_dir(nodo **raiz)
{
    rotacao_esq(&(*raiz)->esq);
    rotacao_dir(raiz);
}

void rotacao_dir_esq(nodo **raiz)
{
    rotacao_dir(&(*raiz)->dir);
    rotacao_esq(raiz);
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

/*Calcula a altura de um nó*/
int alt_no(nodo *no)
{
    if (!no)
        return -1;
    return no->alt;
}

/*retorna o maior valor*/
int maior(int a, int b)
{
    if (a > b)
        return a;
    return b;
}
