#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "lib_trie.h"

int main(int argc, char *argv[])
{
    TrieNode *root;
    FILE *base, *arquivo;
    char str[TAM_PALAVRA];
    
    /* Verifica se os argumentos foram passados corretamente */
    if (argc != 3)
    {
        printf("Uso: %s <arquivo base de dados> <arquivo para inserção>\n", argv[0]);
        return 1;
    }
    /* Abre a base modo leitura binaria, para importar*/
    if (!(base = fopen(argv[1], "wb")))
        return 1;
    if (!(arquivo = fopen(argv[2], "r")))
        return 1;

    root =  import_trie(base);
    if(!root)
        root = cria_nodo_trie();
    /* Fecha a base */
    fclose(base);

    /* Insere as palavras do arquivo na trie */
    while (!feof(arquivo))
    {
        char palavra[TAM_PALAVRA];
        fscanf(arquivo, "%25s", palavra);
        retira_pontuacao(palavra);
        tudo_minusculo(palavra);
        if (!tem_acento(palavra) && strlen(palavra) >= 4)
            inserir_trie(root, palavra, argv[2]);
    }
    fclose(arquivo);

    /* Abre a base modo escrita binaria, para exportar*/
    if (!(base = fopen(argv[1], "ab")))
        return 1;
    export_trie(base, root);
    
    fclose(base);
    destroi(root);
    return 0;
}
