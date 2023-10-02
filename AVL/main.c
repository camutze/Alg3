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
        scanf("%c %d", &op, &r);
        
        switch (op)
        {
        case 'i':
            insere_nodo(avl->raiz, r);
            imprime(avl->raiz);
            printf("\n");
            break;
        case 'b':
            busca(avl->raiz, r);
            printf("\n");
            break;
        case 'r':
            remove_nodo(avl->raiz, r);
            imprime(avl->raiz);
            printf("\n");
            break;
         case 's':
            break;
        default:
            printf("Operacao invalida\n");
            break;
        }
        
    } while (op != 's');

    destruir_arvore(avl->raiz);
    free(avl);
    return 0;
}
