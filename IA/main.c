#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "trie_t.h"

int main(int argc, char **argv)
{
    FILE *base, *arq;

    setlocale(LC_ALL, "pt_BR.UTF-8");


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
        if (strlen(palavra) > 4)
        {
            printf("\n\nORIGINAL: %s\n", palavra);
            word_pontua(palavra);
            printf("PONTUADA: %s\n", palavra);
            if(word_tem_acento(palavra))
                printf("TEM ACENTO\n");
            else
                printf("NÃO TEM ACENTO\n\n\n");
        }

    }
    fclose(base);
    fclose(arq);
    }
