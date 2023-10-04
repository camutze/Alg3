#include <stdio.h>
#include <stdlib.h>
#include "avl-tree.h"

int main()
{
    arvore *avl;
    int r;
    char op;
    avl = cria_arvore();

    do
    {
        scanf("%c", &op);
        scanf("%d", &r);
        switch (op)
        {
        case 'i':
            printf("Inserindo %d\n", r);
            avl->raiz = insere_nodo(avl->raiz, r);
            imprime(avl->raiz);
            printf("\n");
            break;
        case 'b':
            busca(avl->raiz, r);
            printf("\n");
            break;
        case 'r':
            avl->raiz = remove_nodo(avl->raiz, r);
            imprime(avl->raiz);
            printf("\n");
            break;
        case 's':
            break;
        }

    } while (op != 's');

    destruir_arvore(avl->raiz);
    free(avl);
    return 0;
}
