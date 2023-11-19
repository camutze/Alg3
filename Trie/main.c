#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "trie_t.h"

FILE *cria_base()
{
    FILE *base;
    base = fopen("base.txt", "w");
    if (!base)
        tratar_erro("ERRO_AO_CRIAR_ARQUIVO");

    return base;
}
int main(int argc, char **argv)
{
    trie_node *raiz;
    FILE *base, *arq;

    setlocale(LC_CTYPE, "");

    if (argc < 1)
        tratar_erro("ERRO_FALTA_PARAMETRO 25");

    if (strcmp(argv[1], "base.txt")) // se for difente de base.txt
    {
        if (!(base = cria_base()))
            tratar_erro("ERRO_AO_CRIAR_ARQUIVO 26");

        arq = fopen(argv[1], "r");
    }
    else
        tratar_erro("A BASE NAO PODE SER A MESMA DO ARQUIVO DE ENTRADA");

    printf("Origem do arquivo: %d\n", argc);
    printf("Origem do arquivo: %s\n", argv[1]);

    //

    raiz = criar_no();

    while (!feof(arq))
    {
        char palavra[100];
        fscanf(arq, "%s", palavra);

        word_pontua(palavra);
        if (word_acento(palavra) && strlen(palavra) >= 4)
        {
            word_sem_minusc(palavra);
            printf("%s\n", palavra);
            trie_inserir(raiz, palavra);
        }
    }
    fclose(arq);
    fclose(base);

    trie_imprime(raiz);
    trie_destruir(raiz);
}
