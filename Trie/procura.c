
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "lib_trie.h"

int main(int argc, char *argv[])
{
    TrieNode *root;
    FILE *base, *arquivo;
    /*UM COMENTARIO, QUALQUER COISA*/
    if (argc != 3)
    {
        printf("Uso: %s <arquivo base de dados> <PREFIXO>\n", argv[0]);
        return 1;
    }
    if (!(base = fopen(argv[1], "rb")))
    {
        printf("Erro ao abrir o arquivo %s\n", argv[1]);
        return 1;
    }
    root = import_trie(base);

    if(!root)
    {
        printf("ARVORE VAZIA\n");
        return 1;
    }
    
    printf("Arquivo \"%s\" importado na arvore com sucesso!\n", argv[1]);
    printf("BUSCANDO...%s:\n", argv[2]);
    char str[TAM_PALAVRA];
    
    print_prefix(root, argv[2]);


    fclose(base);
    destroi(root);
    return 0;
}
