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

    printf("(%d)", no->r);
    if (r == no->r)
        return 1;

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

int insere(nodo *no, int r)
{

    if (!no)
    {
        /*Caso onde encontrou uma folha para a inserção*/
        no = cria_nodo(r);
        return 1;
    }

    /*Calcula se a inserção vai ser a esquerda da arvore*/
    if (r < no->r)
    {
        /*sea inserção funciou, eu entro no if e testo balanceamento*/
        if (!insere(no->esq, r))
            return 0;

        if (fator_balanceamento(no) >= 2)
        {
            if (r < no->esq->r)
                rotacao_dir(&no);
            else
                rotacao_dir_esq(&no);
        }
        no->alt = maior_altura(no->esq, no->dir) + 1; // atualiza a altura do nó
        return 1;
    }

    /*não foi a esquerda, testo se insiro a direita*/
    else if (r < no->r)
    {
        if (!insere(no->dir, r))
            return 0;

        if (fator_balanceamento(no) >= 2)
        {
            if (r < no->esq->r)
                rotacao_dir(&no);
            else
                rotacao_esq_dir(&no);
        }
        no->alt = maior_altura(no->esq, no->dir) + 1; // atualiza a altura do nó
        return 1;
    }
    return 0;
}
// calcula o fator de balanceamento de um nó

int remover(nodo *no, int r)
{
    if (!no)
        return 0;

    int res; // resultado da busca

    if (r < no->r)
    {
        if (res = remover(no->esq, r))
        {

            if (fator_balanceamento(no) >= 2)
            {
                if (alt_no(no->dir->esq) <= alt_no(no->dir->dir))
                    rotacao_dir(no);
                else
                    rotacao_esq_dir(no);
            }
        }
    }
    else if (r > no->r)
    {
        if ((res = remover(no->dir, r)))
        {
            if (fator_balanceamento(no) >= 2)
            {
                if (alt_no(no->esq->dir) <= alt_no(no->esq->esq))
                    rotacao_dir(no);
                else
                    rotacao_esq_dir(no);
            }
        }
    }
    /*entra nesse else se for igual*/
    else
    {
        nodo *no_aux;
        if (!no->esq || !no->dir)
        {
            nodo *no_aux = no;

            /* se nao tem filho a esquerda,
            entao o filho a direita vira o pai,
            e vice versa*/
            if (!no->esq)
                no = no->dir;
            else
                no = no->esq;
            free(no_aux);
        }
        /*Nesse caso o nó tem 2 filhos*/
        else
        {
            no_aux = procura_menor(no->dir);
            no->r = no_aux->r;

            remover(no->dir, no_aux->r);

            if (fator_balanceamento(no) >= 2)
            {
                if (alt_no(no->esq->dir) <= alt_no(no->esq->esq))
                    rotacao_dir(no);
                else
                    rotacao_dir_esq(no);
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
    return labs(alt_no(no->esq) - alt_no(no->dir));
}
void rotacao_esq(nodo **raiz)
{
    nodo *no_aux;

    no_aux = (*raiz)->dir;
    (*raiz)->dir = no_aux->esq;

    no_aux->esq = *raiz;

    (*raiz)->alt = maior_altura((*raiz)->esq, (*raiz)->dir) + 1;

    *raiz = no_aux;
}

void rotacao_dir(nodo **raiz)
{
    if (!raiz)
        return;

    nodo *no_aux;
    /*nesse caso o nó */

    no_aux = (*raiz)->esq;
    (*raiz)->esq = no_aux->dir;
    no_aux->dir = *raiz;

    (*raiz)->alt = maior_altura((*raiz)->esq, (*raiz)->dir) + 1;
    no_aux->alt = maior_altura(no_aux->esq, no_aux->dir) + 1;

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
