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

nodo *insere_nodo(nodo *raiz, int r)
{
    if (!raiz)
    {
        /* Caso onde encontrou uma folha para a inserção */
       return cria_nodo(r);
    }

    if (r < raiz->r)
    {
        /* Insere à esquerda e atualiza a altura */
        raiz->esq = insere_nodo(raiz->esq, r);
    }

    else if (r > raiz->r)
    {
        /* Insere à direita e atualiza a altura */
        raiz->dir = insere_nodo(raiz->dir, r);
    }

    /* Atualiza a altura do nó atual */
    raiz->alt = maior(alt_no(raiz->esq), alt_no(raiz->dir)) + 1;

    /* Verifica e corrige o fator de equilíbrio */
    int fator = fator_balanceamento(raiz);
    if (fator >= 2)
    {
        if (r < raiz->esq->r)
            rotacao_dir(&raiz);
        else
            rotacao_esq_dir(&raiz);
    }
    else if (fator <= -2)
    {
        if (r > raiz->dir->r)
            rotacao_esq(&raiz);
        else
            rotacao_dir_esq(&raiz);
    }

    return raiz;
}

nodo *remove_nodo(nodo *raiz, int r)
{
    /* Nó não encontrado, nenhum trabalho a fazer. */
    if (!raiz)
        return raiz;

    /* Remova da subárvore esquerda e atualize a altura. */
    if (r < raiz->r)
        raiz->esq = remove_nodo(raiz->esq, r);

    /* Remova da subárvore direita e atualize a altura. */
    else if (r > raiz->r)
        raiz->dir = remove_nodo(raiz->dir, r);

    else
    {
        /* Nodo com o valor a ser removido encontrado. */

        /* Caso 1: Nodo com zero ou um filho. */
        if (!raiz->esq || !raiz->dir)
        {
            /*Camila, aqui é tipo um if, me pergunte depois
            variavel = (condicao) ? valor_se_verdadeiro : valor_se_falso;*/
            nodo *temp = raiz->esq ? raiz->esq : raiz->dir;

            /* Caso 1a: Nodo com zero filho. */
            if (!temp)
            {
                temp = raiz;
                raiz = NULL;
            }
            /* Caso 1b: Nodo com um filho. */
            else
            {
                *raiz = *temp; /* Copia os conteúdos do filho para o nodo atual. */
                free(temp);    /* Libera a memória do nodo filho. */
            }
        }
        else /* Caso 2: Nodo com dois filhos. */
        {
            /* Encontre o sucessor in-order (o menor valor na subárvore direita). */
            nodo *temp = procura_menor(raiz->dir);

            /* Copie o valor do sucessor para este nodo. */
            raiz->r = temp->r;

            /* Remova o sucessor in-order. */
            raiz->dir = remove_nodo(raiz->dir, temp->r);
        }
    }

    /* Se a raiz se tornar nula após a remoção, retorne-a. */
    if (!raiz)
        return raiz;

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
    return alt_no(no->esq) - alt_no(no->dir);
}
void rotacao_esq(nodo **raiz)
{
    /* Verifica se a raiz é nula, se a raiz não possui um filho direito ou se a rotação esquerda não é possível. */
    if (!raiz || !(*raiz) || !(*raiz)->dir)
        return;

    /* Armazena os ponteiros para o nodo raiz e o nodo direito em variáveis locais. */
    nodo *nodo_raiz = *raiz;
    nodo *nodo_dir = (*raiz)->dir;

    /* Realiza a rotação esquerda trocando os ponteiros da subárvore direita e o nodo raiz. */
    nodo_raiz->dir = nodo_dir->esq;
    nodo_dir->esq = nodo_raiz;

    /* Atualiza as alturas dos nodos afetados. */
    nodo_raiz->alt = maior(alt_no(nodo_raiz->esq), alt_no(nodo_raiz->dir)) + 1;
    nodo_dir->alt = maior(alt_no(nodo_dir->esq), alt_no(nodo_dir->dir)) + 1;

    /* Atualiza a raiz da árvore para apontar para o novo nodo raiz (anteriormente o nodo direito). */
    *raiz = nodo_dir;
}

void rotacao_dir(nodo **raiz)
{
    /* Verifica se a raiz é nula, se a raiz não possui um filho esquerdo ou se a rotação direita não é possível. */
    if (!raiz || !(*raiz) || !(*raiz)->esq)
        return;

    /* Armazena os ponteiros para o nodo raiz e o nodo esquerdo em variáveis locais. */
    nodo *nodo_raiz = *raiz;
    nodo *nodo_esq = (*raiz)->esq;

    /* Realiza a rotação direita trocando os ponteiros da subárvore esquerda e o nodo raiz. */
    nodo_raiz->esq = nodo_esq->dir;
    nodo_esq->dir = nodo_raiz;

    /* Atualiza as alturas dos nodos afetados. */
    nodo_raiz->alt = maior(alt_no(nodo_raiz->esq), alt_no(nodo_raiz->dir)) + 1;
    nodo_esq->alt = maior(alt_no(nodo_esq->esq), alt_no(nodo_esq->dir)) + 1;

    /* Atualiza a raiz da árvore para apontar para o novo nodo esquerdo (anteriormente o nodo raiz). */
    *raiz = nodo_esq;
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
