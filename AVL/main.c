#include <stdio.h>
#include <stdlib.h>
#include "avl-tree.h"

int main()
{
    arvore *avl;
    nodo *raiz_aux;
    int r;
    char op;
    avl = cria_arvore();

    while (scanf("%c %d", &op, &r) != EOF)
    {
        raiz_aux = retorna_raiz(avl);
        
        switch (op)
        {
        case 'i':
            raiz_aux = insere_nodo(raiz_aux, r);
            printf("\ni %d\n", r);
            imprime(raiz_aux);
            break;
        case 'b':
            printf("\nb %d\n", r);
            busca(raiz_aux, r);
            break;
        case 'r':
            raiz_aux = remove_nodo(avl->raiz, r);
            printf("\nr %d\n", r);
            imprime(raiz_aux);
            break;
        }
        salva_raiz(avl, raiz_aux);
    }

    destruir_arvore(retorna_raiz(avl));
    free(avl);
    return 0;
}
