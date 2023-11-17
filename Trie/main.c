#include <stdio.h>
#include <stdlib.h>

#include "trie_t.h"

int main()
{
    trie_node *raiz;
    raiz = criar_no();
    FILE *arq;
    
    arq = fopen("palavras.txt", "r");// nome do arquivo e modo de abertura, r é de read
    if(!arq)
        tratar_erro("ERRO_ABRIR_ARQUIVO"); // arrumar isso aqui
    
     while(!feof(arq))
    {
        char palavra[100];
        fscanf(arq, "%s", palavra);
        /*Testar se é maior que 3, verifica se é fim*/
        /*Wiki do maziero, prog 2, strings*/

        printf("%s\n", palavra);
    }
    
    fclose(arq);
    
    inserir(raiz, "teste");
    inserir(raiz, "testando");
    imprime(raiz);
    destruir_trie(raiz);
}
