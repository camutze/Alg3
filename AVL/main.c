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
            insere(avl->raiz, r);
            break;
        case 'b':
            busca(avl->raiz, r);
            break;
        case 'r':
            remover(avl->raiz, r);
            break;
        case '\n':
            return 0;
        default:
            break;
        }
    } while (op != 'i' || op != 'b' || op != 'r');

    destruir_arvore(avl->raiz);
    free(avl);
    return 0;
}
