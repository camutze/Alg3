#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "trie_t.h"

int main(int argc, char **argv)
{
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


    while (!feof(arq))
    {
        char palavra[100];
        fscanf(arq, "%s", palavra);
        
        word_pontua(palavra);
        if (word_acento(palavra) && strlen(palavra) >= 4)
        {
            word_sem_minusc(palavra);
            printf("%s\n", palavra);
            fprintf(base, "%s %s\n", palavra, argv[2]);
            
        }
    }
   
}
