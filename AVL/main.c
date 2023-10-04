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

    do
    {
        raiz_aux = retorna_raiz(avl);
        scanf("%c %d", &op, &r);

        switch (op)
        {
        case 'i':
            raiz_aux = insere_nodo(raiz_aux, r);
            imprime(raiz_aux);
            printf("\n");
            break;
        case 'b':
            busca(raiz_aux, r);
            printf("\n");
            break;
        case 'r':
            raiz_aux = remove_nodo(avl->raiz, r);
            imprime(raiz_aux);
            printf("\n");
            break;
        }
        salva_raiz(avl, raiz_aux);
    } while (op != 's');

    destruir_arvore(retorna_raiz(avl));
    free(avl);
    return 0;
}
