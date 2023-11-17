#include "trie_t.h"

int main()
{
    trie_node *raiz;
    raiz = criar_no();

    inserir(raiz, "teste");
    inserir(raiz, "testando");
    imprime(raiz);
    destruir_trie(raiz);
}
