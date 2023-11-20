#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "trie_t.h"

int main(int argc, char **argv)
{
    FILE *base, *arq;
    trie_node *raiz;
    setlocale(LC_ALL, "pt_BR.UTF-8");

    printf("argc: %d\n", argc);
    if (argc < 3)
        tratar_erro("ERRO_FALTA_PARAMETRO");

    if (!(base = fopen(argv[1], "a")))
        tratar_erro("ERRO_AO_ABRIR_ARQUIVO_BASE");

    if (!(arq = fopen(argv[2], "r")))
        tratar_erro("ERRO_AO_ABRIR_ARQUIVO_ARQ");

    raiz = criar_no();

    while (!feof(arq))
    {
        char palavra[100];
        fscanf(arq, "%s", palavra);
        word_pontua(palavra);
        if (strlen(palavra) > 4 && word_tem_acento(palavra))
        {
            trie_inserir(raiz, palavra, argv[2]);

        }
    }
    trie_destruir(raiz);
    fclose(base);
    fclose(arq);
}
