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
    if (!no)
        return 0;

    printf("%d", no->r);
    if (r == no->r)
        return 1;
    if (no->esq || no->dir)
        printf(",");

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
    printf("%d, ", no->r);

    imprime(no->esq);
    printf(", ");

    imprime(no->dir);

    printf(")");
}

nodo *insere_nodo(nodo *raiz, int r)
{
    /* Insere se arvore vazia. */
    if (!raiz)
        return cria_nodo(r);      
    /* Se o valor a ser inserido for menor ou igual que o valor do nodo, insere a esquerda. */
    if (r <= raiz->r)
        raiz->esq = insere_nodo(raiz->esq, r);
    /* Caso contrario, insere a direita. */
    else
        raiz->dir = insere_nodo(raiz->dir, r);

    /* Refaz o calculo da altura. */
    raiz->alt = maior(alt_no(raiz->esq), alt_no(raiz->dir)) + 1;

    raiz = balancear(raiz);

    return raiz;
}

void troca_nodo(nodo *raiz, nodo *aux)
{
    nodo *troca;

    troca = raiz;
    raiz = aux;
    aux = troca;
}

nodo *remove_nodo(nodo *raiz, int r)
{
    nodo *aux;

    if (!raiz)
        return NULL;
    /* Encontrou o nodo a ser removido. */
    if (r == raiz->r)
    {
        /*comentar os casos
        https://youtu.be/qsEKOzC62Zw?si=a6bRbAGIKwdqe_Vg*/

        /* Caso 1 - nodo sem filhos. */
        if (!raiz->esq && !raiz->dir)
        {
            free(raiz);
            return NULL;
        }
        /* Caso 2 - dois filhos. */
        if (raiz->esq && raiz->dir)
        {
            aux = raiz->esq;
            while (aux->dir)
                aux = aux->dir;

            troca_nodo(raiz, aux);

            raiz->esq = remove_nodo(raiz->esq, r);
            return raiz;
        }
        /* caso 3 um filho. */
        if (raiz->esq)
            aux = raiz->esq;
        else
            aux = raiz->dir;

        free(raiz);
        return aux;
    }
    /* Caso o chave ainda nao tenha sido encontrada e esta for menor que o valor do nodo atual. */
    if (r < raiz->r)
        raiz->esq = remove_nodo(raiz->esq, r);
    /* Chave ainda nao encontrada e valor maior que o do nodo atual. */
    else
        raiz->dir = remove_nodo(raiz->dir, r);

    /* Recalcula a altura. */
    raiz->alt = maior(alt_no(raiz->esq), alt_no(raiz->dir)) + 1;
    /* Garante que a arvore continua balanceada depois de cada remocao. */
    raiz = balancear(raiz);

    return raiz;
}

nodo *balancear(nodo *raiz)
{
    short fator;
    /* Esta parte da funcao faz o calculo do balanceamento e chama a rotacao necessaria em cada caso. */
    fator = fator_balanceamento(raiz);
    /* Rotação a esquerda. */
    if (fator < -1 && fator_balanceamento(raiz->dir) <= 0)
        return rotacao_esq(raiz);

    /* Rotação a direita. */
    if (fator > 1 && fator_balanceamento(raiz->esq) >= 0)
        return rotacao_dir(raiz);

    /* Rotação dupla a esquerda. */
    if (fator > 1 && fator_balanceamento(raiz->esq) < 0)
        return rotacao_esq_dir(raiz);

    /* Rotação dupla a direita. */
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
    return no ? no->alt : -1;
}

short maior(int a, int b)
{
    return (a > b) ? a : b; 
}

nodo *retorna_raiz(arvore *avl)
{
    return avl->raiz;
}
/* Grava endereco atual da raiz para nao violar TAD. */
void salva_raiz(arvore *avl, nodo *raiz)
{
    avl->raiz = raiz; /* Encapsulamento. */
}

void destruir_arvore(nodo *no)
{
    if (!no)
        return;
    /*Checa primeiro o lado esquerdo da arvore, e depois o direito. */
    destruir_arvore(no->esq);    
    destruir_arvore(no->dir);
    /* Entra caso esse nodo exista e os filhos desse sejam nulos. */
    free(no);

    return;
}