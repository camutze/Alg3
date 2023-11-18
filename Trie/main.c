#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "trie_t.h"

int main()
{
    trie_node *raiz;
    raiz = criar_no();
    FILE *arq;

    setlocale(LC_CTYPE, "");

    arq = fopen("palavras.txt", "r"); // nome do arquivo e modo de abertura, r é de read
    if (!arq)
        tratar_erro("ERRO_ABRIR_ARQUIVO"); // arrumar isso aqui

    while (!feof(arq))
    {
        char palavra[100];
        fscanf(arq, "%s", palavra);
        remove_pontuacao(palavra);
        if (!tem_acento(palavra) && strlen(palavra) >= 4)
        {
            converte_minusculas(palavra);
            printf("%s\n", palavra);
        }
    }
    imprime(raiz);
    fclose(arq);

    imprime(raiz);
    destruir_trie(raiz);
}
