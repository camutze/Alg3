#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "trie_t.h"

int main()
{
    trie_node *raiz;
    FILE *arq;

    raiz = criar_no();

    setlocale(LC_CTYPE, "");

    arq = fopen("palavras.txt", "r"); // nome do arquivo e modo de abertura, r é de read
    if (!arq)
        tratar_erro("ERRO_ABRIR_ARQUIVO"); // arrumar isso aqui

    while (!feof(arq))
    {
        char palavra[100];
        fscanf(arq, "%s", palavra);
    
        word_pontua(palavra);
        if (!word_acento(palavra) && strlen(palavra) >= 4)
        {
            word_minusc(palavra);
            printf("%s\n", palavra);
            trie_inserir(raiz, palavra);
        }
    }
    fclose(arq);
    
    trie_destruir(raiz);
}
