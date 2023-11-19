#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "trie_t.h"

int main(int argc, char **argv)
{
    arvore_trie *arvore;
    FILE *base, *arq;

    setlocale(LC_CTYPE, "");
    /* tres casos
        base.txt arquivo
        arquivo.txt
        base.txt*/

    printf("argc: %d\n", argc);
    if (argc < 3)
        tratar_erro("ERRO_FALTA_PARAMETRO");

    if (!(base = fopen(argv[1], "a")))
        tratar_erro("ERRO_AO_ABRIR_ARQUIVO_BASE");
        
    if (!(arq = fopen(argv[2], "r")))
        tratar_erro("ERRO_AO_ABRIR_ARQUIVO_ARQ");

    arvore = criar_arvore(argv[1], base);

    while (!feof(arq))
    {
        char palavra[100];
        fscanf(arq, "%s", palavra);

        word_pontua(palavra);
        if (word_acento(palavra) && strlen(palavra) >= 4)
        {
            word_sem_minusc(palavra);
            printf("%s\n", palavra);
            trie_inserir(arvore->raiz, palavra);

            fprintf(base, "%s %s\n", palavra, argv[2]);
            
        }
    }
    fclose(arq);
    fclose(base);

    trie_imprime(arvore->raiz);
    trie_destruir_nodo(arvore->raiz);
    free(arvore->arquivos);
    free(arvore);
}
