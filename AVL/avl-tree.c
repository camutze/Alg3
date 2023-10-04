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

    if (!(filho = malloc(sizeof(nodo))))
        return NULL;

    filho->r = r;
    filho->dir = NULL;
    filho->esq = NULL;
    filho->alt = 0;

    return filho;
}

int busca(nodo *no, int r)
{
    /*Arrumar a virgula*/
    if (!no)
        return 0;

    printf("%d", no->r);
    if (r == no->r)
        return 1;

    /*corrigir isso daqui*/
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
    printf("%d", no->r);

    imprime(no->esq);
    printf(", ");

    imprime(no->dir);

    printf(")");
}

nodo *insere_nodo(nodo *raiz, int r)
{
    /*Arvore vazia*/
    if (!raiz)
        return cria_nodo(r);
    /*Se o valor a ser inserido for menor ou igual que
    o valor do nodo, insere a esquerda*/
    if (r <= raiz->r)
        raiz->esq = insere_nodo(raiz->esq, r);
    /*Se o valor a ser inserido for maior que o valor do nodo,
    insere a direita*/
    else
        raiz->dir = insere_nodo(raiz->dir, r);

    /*recalcula a altura */
    raiz->alt = maior(alt_no(raiz->esq), alt_no(raiz->dir)) + 1;

    raiz = balancear(raiz);

    return raiz;
}

nodo *remove_nodo(nodo *raiz, int r)
{
    nodo *aux;

    if (!raiz)
        return NULL;

    if (r == raiz->r)
    {
        /*comentar os casos
        https://youtu.be/qsEKOzC62Zw?si=a6bRbAGIKwdqe_Vg*/

        /*caso 1 sem filhos*/
        if (!raiz->esq && !raiz->dir)
        {
            free(raiz);
            return NULL;
        }
        /*caso 2 dois filhos*/
        if (raiz->esq && raiz->dir)
        {
            aux = raiz->esq;
            while (aux->dir)
                aux = aux->dir;
            /*ATENÇÃO
            testar sem trocar os valores, mas sim trocar
            os ponteiros*/
            raiz->r = aux->r;
            aux->r = r;
            raiz->esq = remove_nodo(raiz->esq, r);
            return raiz;
        }
        /*caso 3 um filho*/
        if (raiz->esq)
            aux = raiz->esq;
        else
            aux = raiz->dir;

        free(raiz);
        return aux;
    }
    if (r < raiz->r)
        raiz->esq = remove_nodo(raiz->esq, r);
    else
        raiz->dir = remove_nodo(raiz->dir, r);
    
    /*recalcula a altura */
    raiz->alt = maior(alt_no(raiz->esq), alt_no(raiz->dir)) + 1;

    raiz = balancear(raiz);

    return raiz;
}

nodo *balancear(nodo *raiz)
{
    short fator;

    fator = fator_balanceamento(raiz);
    /*Rotação a esquerda*/
    if (fator < -1 && fator_balanceamento(raiz->dir) <= 0)
        return rotacao_esq(raiz);

    /*Rotação a direita*/
    if (fator > 1 && fator_balanceamento(raiz->esq) >= 0)
        return rotacao_dir(raiz);

    /*Rotação dupla a esquerda*/
    if (fator > 1 && fator_balanceamento(raiz->esq) < 0)
        return rotacao_esq_dir(raiz);

    /*Rotação dupla a direita*/
    if (fator < -1 && fator_balanceamento(raiz->dir) > 0)
        return rotacao_dir_esq(raiz);

    return raiz;
}

nodo *rotacao_dir(nodo *raiz)
{
    nodo *aux;

    aux = raiz->esq;

    raiz->esq = aux->dir;
    aux->dir = raiz;

    raiz->alt = maior(alt_no(raiz->esq), alt_no(raiz->dir)) + 1;
    aux->alt = maior(alt_no(aux->esq), raiz->alt) + 1;

    return aux;
}

nodo *rotacao_esq(nodo *raiz)
{
    nodo *aux;

    aux = raiz->dir;

    raiz->dir = aux->esq;
    aux->esq = raiz;

    raiz->alt = maior(alt_no(raiz->esq), alt_no(raiz->dir)) + 1;
    aux->alt = maior(alt_no(aux->dir), raiz->alt) + 1;

    return aux;
}

nodo *rotacao_esq_dir(nodo *raiz)
{
    raiz->esq = rotacao_esq(raiz->esq);
    return rotacao_dir(raiz);
}

nodo *rotacao_dir_esq(nodo *raiz)
{
    raiz->dir = rotacao_dir(raiz->dir);
    return rotacao_esq(raiz);
}

short fator_balanceamento(nodo *no)
{
    return no ? alt_no(no->esq) - alt_no(no->dir) : 0;
}

/*Retorna a altura de um nó ou -1 caso NULL*/
short alt_no(nodo *no)
{
    if (!no)
        return -1;
    else
        return no->alt;
}

short maior(int a, int b)
{
    return (a > b) ? a : b;
}

nodo *retorna_raiz(arvore *avl)
{
    return avl->raiz;
}

void destruir_arvore(nodo *no)
{
    if (!no)
        return;
    destruir_arvore(no->dir);
    destruir_arvore(no->esq);

    free(no);

    return;
}