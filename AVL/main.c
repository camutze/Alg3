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
            insere_nodo(&(avl->raiz), r);
            imprime(avl->raiz);
            printf("\n");
            break;
        case 'b':
            busca(avl->raiz, r);
            printf("\n");
            break;
        case 'r':
            remove_nodo(&(avl->raiz), r);
            imprime(avl->raiz);
            printf("\n");
            break;
        // case '\n':
        //     return 0;
        default:
            break;
        }
        
    } while (op != 'i' || op != 'b' || op != 'r');

    destruir_arvore(avl);
    free(avl);
    return 0;
}
