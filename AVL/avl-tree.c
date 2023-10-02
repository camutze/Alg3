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
    printf("%d,", no->r);

    imprime(no->esq);
    printf(",");

    imprime(no->dir);

    printf(")");
}
/*Comentar isso aqui*/
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

nodo *insere_nodo(nodo *raiz, int *r)
{
    if (!raiz)
    {
        /* Caso onde encontrou uma folha para a inserção */
        return cria_nodo(&r);
    }

    if (r < raiz->r)
    {
        /* Insere à esquerda e atualiza a altura */
        raiz->esq = insere_recursivo(raiz->esq, r);

        /* Verifica e corrige o fator de equilíbrio */
        int fator = fator_balanceamento(raiz);
        if (fator >= 2)
        {
            if (r < raiz->esq->r)
                rotacao_dir(&raiz);
            else
                rotacao_esq_dir(&raiz);
        }
    }
    else if (r > raiz->r)
    {
        /* Insere à direita e atualiza a altura */
        raiz->dir = insere_recursivo(raiz->dir, r);

        /* Verifica e corrige o fator de equilíbrio */
        int fator = fator_balanceamento(raiz);
        if (fator >= 2)
        {
            if (r > raiz->dir->r)
                rotacao_esq(&raiz);
            else
                rotacao_dir_esq(&raiz);
        }
    }

    /* Atualiza a altura do nó atual */
    raiz->alt = maior(alt_no(raiz->esq), alt_no(raiz->dir)) + 1;

    return raiz;
}

nodo *remove_nodo_recursivo(nodo *raiz, int r)
{
    /* Nó não encontrado, nenhum trabalho a fazer. */
    if (!raiz)
        return raiz;

    /* Remova da subárvore esquerda e atualize a altura. */
    if (r < raiz->r)
        raiz->esq = remove_nodo_recursivo(raiz->esq, r);

    /* Remova da subárvore direita e atualize a altura. */
    else if (r > raiz->r)
        raiz->dir = remove_nodo_recursivo(raiz->dir, r);

    else
    {
        /* Nodo com o valor a ser removido encontrado. */

        /* Caso 1: Nodo com zero ou um filho. */
        if (!raiz->esq || !raiz->dir)
        {
            nodo *temp;
            if (raiz->esq)
                temp = raiz->esq; 
            else
                temp = raiz->dir; 
                
            /* Caso 1a: Nodo com zero filho. */
            if (!temp)
            {
                temp = raiz;
                raiz = NULL;
            }
            else /* Caso 1b: Nodo com um filho. */
            {
                *raiz = *temp; /* Copia os conteúdos do filho para o nodo atual. */
            }

            free(temp);
        }
        else /* Caso 2: Nodo com dois filhos. */
        {
            /* Encontre o sucessor in-order (o menor valor na subárvore direita). */
            nodo *temp = procura_menor(raiz->dir);

            /* Copie o valor do sucessor para este nodo. */
            raiz->r = temp->r;

            /* Remova o sucessor in-order. */
            raiz->dir = remove_nodo_recursivo(raiz->dir, temp->r);
        }
    }

    /* Se a raiz se tornar nula após a remoção, retorne-a. */
    if (!raiz)
    {
        return raiz;
    }

    /* Atualize a altura do nodo atual. */
    raiz->alt = maior(alt_no(raiz->esq), alt_no(raiz->dir)) + 1;

    /* Verifique o fator de equilíbrio do nodo. */
    int fator = fator_balanceamento(raiz);

    /* Se o fator de equilíbrio estiver fora do intervalo [-1, 1], reequilibre a árvore. */
    if (fator >= 2)
    {
        /* Nó desequilibrado na subárvore esquerda. */
        if (fator_balanceamento(raiz->esq) >= 0)
        {
            rotacao_dir(&raiz);
        }
        else
        {
            rotacao_esq_dir(&raiz);
        }
    }
    else if (fator <= -2)
    {
        /* Nó desequilibrado na subárvore direita. */
        if (fator_balanceamento(raiz->dir) <= 0)
        {
            rotacao_esq(&raiz);
        }
        else
        {
            rotacao_dir_esq(&raiz);
        }
    }

    return raiz;
}

int fator_balanceamento(nodo *no)
{
    if (!no)
        return 0;
    /* nao precisa do sinal, pois o labs retorna o valor absoluto */
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
    /*Vazamento de memoria, CORRIJAAAAAAAAAAAA*/
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
