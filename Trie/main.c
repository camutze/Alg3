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

    base = fopen("base.txt", "r");
    if (!base)
        base = cria_base();
    

    arq = fopen(argv[2], "r");
    if (!arq)
        tratar_erro("ERRO_ABRIR_ARQUIVO");

    printf("Origem do arquivo: %s\n", argv[2]);
    

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

    trie_imprime(raiz);
    trie_destruir(raiz);
}
